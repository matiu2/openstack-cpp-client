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
    string _contentType; // The mime content type we should be requesting (basically application/json or application/xml)
    services::HTTPS _connection;
protected:
    /// Returns a connected https reference
    services::HTTPS& connection();
public:
    Servers(const string& hostname, const string& path, const string& authToken, const string& contentType) :
        _hostname(hostname), _pathBase(path), _authToken(authToken), _contentType(contentType), _connection(hostname) {}
    /// Returns a list of servers (in JSON format)
    /// @param details if false will just return servers IDs
    string list(bool details=false);
};

} // namespace net
} // namespace openstack

#endif // SERVERS_HPP
