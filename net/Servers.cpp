#include "Servers.hpp"
#include <sstream>

namespace openstack {
namespace net {

inline services::HTTPS& Servers::connection() {
    if (!_connection.isConnected())
        _connection.connect();
    return _connection;
}

string Servers::list(bool details) {
    using services::HTTPS;
    // Do the request
    HTTPS::Headers requestHeaders, responseHeaders;
    std::stringstream body;
    requestHeaders.insert(HTTPS::Header("X-Auth-Token", _authToken));
    requestHeaders.insert(HTTPS::Header("Accept", "application/json"));
    if (details)
        connection().request(_pathBase + "/servers/detail", requestHeaders, responseHeaders, body);
    else
        connection().request(_pathBase + "/servers", requestHeaders, responseHeaders, body);
    // Parse the body and return the object
    body.seekp(std::stringstream::beg); // Go back to the beginning of our stream
    return body.str();
}

} // namespace net
} // namepsace openstack
