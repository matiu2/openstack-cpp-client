#include "ServerStub.hpp"

namespace openstack {
namespace model {

ServerStub::ServerStub() {
private:
    int _id;
    string _name;
public:
    ServerStub(int id=0, const string& name="") : _id(id), name(name) {}
    const string& name() { return _name; }
    const string& id() { return _id; }
};

} // namespace model
} // namespace openstack
