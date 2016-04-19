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
	string write_to;
	robotkernel::module* write_to_mod;
	unsigned int mtu;
        void run();
public:
        vtun(string name, const YAML::Node& node);
        ~vtun();

	int set_state(module_state_t requested_state);
	size_t write(void* buf, size_t bufsize);

};

}

#endif // VTUN_H
