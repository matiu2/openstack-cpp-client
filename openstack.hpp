/*
 * =====================================================================================
 *
 *       Filename:  openstack.hpp
 *
 *    Description:  The main header file to import to get openstack client running
 *
 *        Version:  1.0
 *        Created:  28/07/11 12:09:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef OPENSTACK_HPP
#define OPENSTACK_HPP

#include "https.hpp"
#include "servers.hpp"
#include <boost/shared_ptr.hpp>
#include "url.hpp"

using boost::shared_ptr;

namespace openstack {

class Openstack {
private:
    string _user;
    string _apikey;
    string _hostname;
    string _authToken;
    string _cdnUrl;
    string _serverUrl;
    string _storageUrl;
    string _storageToken;

    HTTPS _connection;
    shared_ptr<Servers> _servers;

    string readHeader(const HTTPS::Headers& headers, const string& headerName) {
        HTTPS::cpHeader contentLengthHeader = headers.find(headerName);
        if (contentLengthHeader != headers.end()) {
            return (*contentLengthHeader).second;
        } else {
            return "";
        }
    }
    void auth() {
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
    HTTPS& connection() {
        if (!_connection.isConnected()) {
            _connection.connect();
            auth();
        }
        return _connection;
    }
public:
    Openstack(const string& user, const string& apikey, const string& hostname) 
        : _user(user), _apikey(apikey), _hostname(hostname), _connection(hostname) {}
    shared_ptr<Servers> servers() {
        if (_servers.get() == 0) {
            if (_serverUrl.empty()) { connection(); } // Get the serverurl if we haven't already
            std::pair<string, string> hostAndPath = getHostAndPath(_serverUrl);
            _servers.reset(new Servers(hostAndPath.first, hostAndPath.second, _authToken));
        }
        return _servers;
    }
};

} // namespace openstack

#endif // OPENSTACK_HPP
