#ifndef VTUN_H

#include <string>

#include <robotkernel/kernel.h>
#include <robotkernel/helpers.h>
#include <robotkernel/runnable.h>
#include <robotkernel/module_base.h>

#include <yaml-cpp/yaml.h>

namespace module_vtun {

using namespace std;

class vtun
	: public robotkernel::runnable, 
	  public robotkernel::module_base {

	int fd;
	string if_name;
        void run();
public:
        vtun(string name, const YAML::Node& node);
        ~vtun();

	int set_state(module_state_t requested_state);
};

}

#endif // VTUN_H
