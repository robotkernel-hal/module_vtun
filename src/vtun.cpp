#include "vtun.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#include <string_util/string_util.h>

#include <string>

using namespace std;
using namespace robotkernel;

MODULE_DEF(module_vtun, module_vtun::vtun)

namespace module_vtun {

#if !defined(HAVE_GETTID)
int gettid() {
#ifdef __NR_gettid
	return syscall( __NR_gettid );
#else
	return 0;
#endif
}
#endif


vtun::vtun(string name, const YAML::Node& node)
	: runnable(node), module_base("vtun", name, node) {

	fd = -1;
}

vtun::~vtun() {
	if(state != module_state_init)
		set_state(module_state_init);
}


int vtun::set_state(module_state_t requested_state) {
	log(info, "state %s requested\n", state_to_string(requested_state));
	switch (requested_state) {
	case module_state_init: {
		stop();
		if(fd != -1) {
			close(fd);
			fd = -1;
		}
		break;
        }
        case module_state_preop: {
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
		break;
        }
        case module_state_safeop: {
		start();
		break;
        }
        case module_state_op:
		break;
	default:        
		// invalid state 
		// nothing todo
		// return -1;
		break;
	}
	state = requested_state;
	
	return 0;
}

void vtun::run() {
	log(info, "vtun tid %d started!\n", gettid());
	
	while (running()) {

		sleep(1);
	}

	log(info, "vtun handler %d stopping\n", gettid());
}


}
