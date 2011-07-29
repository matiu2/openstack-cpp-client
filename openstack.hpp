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

#include "https.hpp"
#include "iostream"

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
    HTTPS connection;
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
        connection.request("/v1.0", requestHeaders, responseHeaders, body);
        // Read in what we care about
        _authToken = readHeader(responseHeaders, "x-auth-token");
        _cdnUrl = readHeader(responseHeaders, "x-cdn-management-url");
        _serverUrl = readHeader(responseHeaders, "x-server-management-url");
        _storageUrl = readHeader(responseHeaders, "x-storage-url");
        _storageToken = readHeader(responseHeaders, "x-storage-token");
        // Just now for debugging, print it all out
        std::cout << "x-auth-token => " << _authToken << std::endl;
        std::cout << "x-cdn-management-url => " << _cdnUrl << std::endl;
        std::cout << "x-server-management-url => " << _serverUrl << std::endl;
        std::cout << "x-storage-url => " << _storageUrl << std::endl;
        std::cout << "x-storage-token => " << _storageToken << std::endl;
    }
public:
    Openstack(const string& user, const string& apikey, const string& hostname) 
        : _user(user), _apikey(apikey), _hostname(hostname), connection(hostname) {}
    void checkConnection() {
        if (!connection.isConnected()) {
            connection.connect();
            auth();
        }
    }
};

} // namespace openstack
