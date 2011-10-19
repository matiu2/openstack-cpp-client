/** Performs the service of downloading the json and handing it to whoever needs it. Doesn't do any parsing
  *
  **/
#ifndef SERVERS_HPP
#define SERVERS_HPP

#include "../services/https.hpp"

namespace openstack {
namespace net {

class Servers {
private:
    string _hostname;
    string _pathBase;
    string _authToken;
    services::HTTPS _connection;
protected:
    /// Returns a connected https reference
    services::HTTPS& connection();
public:
    Servers(const string& hostname, const string& path, const string& authToken) :
        _hostname(hostname), _pathBase(path), _authToken(authToken), _connection(hostname) {}
    /// Returns a list of servers (in JSON format)
    /// @param details if false will just return servers IDs
    string list(bool details=false);
};

} // namespace net
} // namespace openstack

#endif // SERVERS_HPP
