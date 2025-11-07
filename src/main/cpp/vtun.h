//! robotkernel module for vtun
/*!
 * author: Florian Schmidt <florian.schmidt@dlr.de>
 * author: Robert Burger <robert.burger@dlr.de>
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

#include <robotkernel/robotkernel.h>
#include <robotkernel/helpers.h>
#include <robotkernel/runnable.h>
#include <robotkernel/stream.h>
#include <robotkernel/module_base.h>

#include <yaml-cpp/yaml.h>

using namespace std;
using namespace robotkernel;

namespace module_vtun {

class vtun : 
    public enable_shared_from_this<vtun>,
    public module_base,
    public stream
{
    private:
        int fd;                                     //!< tun device file descriptor
        string if_name;                             //!< tun interface name

    public:
        //! de-/construction
        /*
         * \param name vtun name
         * \param node YAML configuration node
         */
        vtun(string name, const YAML::Node& node);
        ~vtun();

        virtual void init() override {
            add_device(static_pointer_cast<stream>(shared_from_this()));
        }

        //! set state
        /*!
         * \param state new state
         */
        virtual int set_state(module_state_t requested_state) override;

        virtual size_t write(void* buf, size_t bufsize) override;
        virtual size_t read(void* buf, size_t bufsize) override;
};

}; // namespace module_vtun 

#endif // VTUN_H

