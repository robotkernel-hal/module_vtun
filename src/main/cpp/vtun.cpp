//! robotkernel module for vtun
/*!
 * author: Florian Schmidt <florian.schmidt@dlr.de>
 */

/*
 * The module_vtun is part of robotkernel.
 *
 * robotkernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * robotkernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with robotkernel.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "vtun.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#include <string_util/string_util.h>

#include <vector>
#include <string>

using namespace std;
using namespace robotkernel;
using namespace string_util;
using namespace module_vtun;

MODULE_DEF(module_vtun, module_vtun::vtun);

#if !defined(HAVE_GETTID)
int gettid() {
#ifdef __NR_gettid
    return syscall( __NR_gettid );
#else
    return 0;
#endif
}
#endif


vtun::vtun(string name, const YAML::Node& node) : 
    module_base("vtun", name, node), stream(name, "vtun")
{
    fd = -1;
}

vtun::~vtun() {
    if(state != module_state_init)
        set_state(module_state_init);
            
    kernel::get_instance()->remove_device(
            std::static_pointer_cast<stream>(shared_from_this()));
}

// set state
int vtun::set_state(module_state_t requested_state) {
    kernel& k = *kernel::get_instance();

    // get transition
    uint32_t transition = GEN_STATE(this->state, requested_state);

    switch (transition) {
        case op_2_safeop:
        case op_2_preop:
        case op_2_init:
            // ====> stop sending commands
            if (    (transition == op_2_safeop))
                break;
        case safeop_2_preop:
        case safeop_2_init:
            // ====> stop receiving measurements
            if (    (transition == op_2_preop) ||
                    (transition == safeop_2_preop))
                break;
        case preop_2_init:
            // ====> deinit devices
            close(fd);
            fd = -1;
        case init_2_init:
            // ====> do nothing
            break;

        case init_2_op:
        case init_2_safeop:
        case init_2_preop: {
            // ====> initial devices            
            fd = open("/dev/net/tun", O_RDWR);
            if(fd == -1)
                throw errno_exception_tb("could not open /dev/net/tun");

            struct ifreq ifr;
            memset(&ifr, 0, sizeof(ifr));
            /* Flags: IFF_TUN   - TUN device (no Ethernet headers) 
             *        IFF_TAP   - TAP device  
             *
             *        IFF_NO_PI - Do not provide packet information  
             */ 
            ifr.ifr_flags = IFF_TUN; 

            if(ioctl(fd, TUNSETIFF, (void *)&ifr))
                throw errno_exception_tb("could not request tun/tap device\n");
            if_name = ifr.ifr_name;
            log(info, "using interface %s\n", if_name.c_str());

            if (    (transition == init_2_preop))
                break;
        }
        case preop_2_op:
        case preop_2_safeop:
            // ====> start receiving measurements
            if (    (transition == init_2_safeop) ||
                    (transition == preop_2_safeop))
                break;
        case safeop_2_op:
            // ====> start sending commands
            break;
        case op_2_op:
        case safeop_2_safeop:
        case preop_2_preop:
            // ====> do nothing
            break;

        default:
            break;
    }

    return (this->state = requested_state);
}

size_t vtun::read(void* buf, size_t bufsize) {
    int len = ::read(fd, buf, bufsize);
    if (len == -1) {
        log(warning, "failed to read max %d bytes from tun device", 10000); //mtu);
        return 0;
    }

    log(verbose, "got net packet of length %d\n", len);
    return len;
}

size_t vtun::write(void* buf, size_t bufsize) {
    // send packet!
    int n = ::write(fd, buf, bufsize);
    if (n == -1)
        log(warning, "wanted to write %d bytes, write() returned %d: %s\n", bufsize, n, strerror(errno));
    else if (n != (int)bufsize)
        log(warning, "wanted to write %d bytes, write() returned %d\n", bufsize, n);

    return n;
}

