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

#ifndef VTUN_H

#include <string>

#include <robotkernel/kernel.h>
#include <robotkernel/helpers.h>
#include <robotkernel/runnable.h>
#include <robotkernel/module_base.h>

#include <yaml-cpp/yaml.h>

namespace module_vtun {
#ifdef EMACS
}
#endif

using namespace std;

class vtun : 
    public robotkernel::runnable, 
    public robotkernel::module_base 
{
    private:
        int fd;                                     //!< tun device file descriptor
        string if_name;                             //!< tun interface name
        string write_to;                            //!< robotkernel stream device to write to
        robotkernel::sp_stream_t write_to_stream;   //!< robotkernel stream deivce
        unsigned int mtu;                           //!< max mtu size

        void run();                                 //!< packet receive thread

    public:
        //! de-/construction
        /*
         * \param name vtun name
         * \param node YAML configuration node
         */
        vtun(string name, const YAML::Node& node);
        ~vtun();

        //! set state
        /*!
         * \param state new state
         */
        int set_state(module_state_t requested_state);

        size_t write(void* buf, size_t bufsize);
};

#ifdef EMACS
{
#endif
}

#endif // VTUN_H

