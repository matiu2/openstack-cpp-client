#include "Servers.hpp"
#include <string>

namespace openstack {

model::ServerStubMap Servers::listServerStubs() {
	std::string raw = _net.list();
	model::ServerStubMap result;
	_parser.readStubs(raw, result);
	return result;
}

} // namespace openstack
