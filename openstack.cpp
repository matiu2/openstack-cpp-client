/*
 * =====================================================================================
 *
 *       Filename:  openstack.cpp
 *
 *    Description:  Openstack object .. father of everything Openstack related
 *
 *        Version:  1.0
 *        Created:  18/10/11 21:06:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "openstack.hpp"

namespace openstack  {

string Openstack::readHeader(const HTTPS::Headers& headers, const string& headerName) {
    HTTPS::cpHeader contentLengthHeader = headers.find(headerName);
    if (contentLengthHeader != headers.end()) {
        return (*contentLengthHeader).second;
    } else {
        return "";
    }
}

void Openstack::auth() {
    HTTPS::Headers requestHeaders, responseHeaders;
    requestHeaders.insert(HTTPS::Header("X-Auth-User", _user));
    requestHeaders.insert(HTTPS::Header("X-Auth-Key", _apikey));
    std::stringstream body;
    connection().request("/v1.0", requestHeaders, responseHeaders, body);
    // Read in what we care about
    _authToken = readHeader(responseHeaders, "x-auth-token");
    _cdnUrl = readHeader(responseHeaders, "x-cdn-management-url");
    _serverUrl = readHeader(responseHeaders, "x-server-management-url");
    _storageUrl = readHeader(responseHeaders, "x-storage-url");
    _storageToken = readHeader(responseHeaders, "x-storage-token");
}

HTTPS& Openstack::connection() {
    if (!_connection.isConnected()) {
        _connection.connect();
        auth();
    }
    return _connection;
}

Servers& Openstack::servers() {
    if (_servers.get() == 0) {
        if (_serverUrl.empty()) { connection(); } // Get the serverurl if we haven't already
        std::pair<string, string> hostAndPath = getHostAndPath(_serverUrl);
        _servers.reset(new Servers(hostAndPath.first, hostAndPath.second, _authToken));
    }
    return *_servers;
}

} // namespace openstack
