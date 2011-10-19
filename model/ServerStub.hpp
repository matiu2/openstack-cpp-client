#ifndef OPENSTACK_MODEL_SERVERSTUB_HPP
#define OPENSTACK_MODEL_SERVERSTUB_HPP

#include <map>
#include <string>
#include <memory>

using std::string;

namespace openstack {
namespace model {

class ServerStub {
private:
    int _id;
    string _name;
public:
    ServerStub(int id, const string& name) : _id(id), _name(name) {}
    int id() const { return _id; }
    void setId(int newId) { _id = newId; }
    const string& name() const { return _name; }
    void setName(const string& newName) { _name = newName; }
};

typedef std::map< int, std::shared_ptr<ServerStub> > ServerStubMap;
typedef std::pair< int, std::shared_ptr<ServerStub> > ServerStubPair;

} // namespace model
} // namespace openstack

#endif // OPENSTACK_MODEL_SERVERSTUB_HPP
