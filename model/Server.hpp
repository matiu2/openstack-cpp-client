#ifndef OPENSTACK_MODEL_SERVER_HPP
#define OPENSTACK_MODEL_SERVER_HPP

#include "ServerStub.hpp"
#include <string>
#include <vector>
#include <map>

namespace openstack {
namespace model {

class Server : public ServerStub {
public:
  typedef std::vector<std::string> AddressList;
    typedef std::map<std::string, std::string> Metadata;
private:
    unsigned long _flavorId; // eg. 1
    std::string _hostId;  // eg. "e4d909c290d0fb1ca068ffaddf22cbd0"
    std::string _status; // eg. "BUILD"
    unsigned short _progress; // eg. 60
    AddressList _publicAddresses;
    AddressList _privateAddresses;
    Metadata _metadata;
public:
    Server(int id, const std::string& name) : ServerStub(id, name) {}
    unsigned long getFlavorId() { return _flavorId; }
    void setFlavorId(unsigned long newFlavorId) { _flavorId = newFlavorId; }
    std::string getHostId() { return _hostId; }
    void setHostId(std::string newHostId) { _hostId = newHostId; }
    std::string getStatus() { return _status; }
    void setStatus(std::string  newStatus) { _status = newStatus; }
    unsigned short getProgress() { return _progress; }
    void setProgress(unsigned short  newProgress) { _progress = newProgress; }
    AddressList& getPublicAddresses() { return _publicAddresses; }
    AddressList& getPrivateAddresses() { return _privateAddresses; }
    Metadata& getMetadata() { return _metadata; }
};

} // namespace model
} // namespace openstack

#endif // OPENSTACK_MODEL_SERVER_HPP
