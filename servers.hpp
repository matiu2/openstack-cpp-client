/*
 * =====================================================================================
 *
 *       Filename:  servers.hpp
 *
 *    Description:  Does all the api commands for listing and playing with servers
 *
 *        Version:  1.0
 *        Created:  30/07/11 03:44:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <sstream>
#include <iostream>

namespace openstack {

class Servers {
private:
    string _token;
    string _hostname;
    HTTPS _connection;
    string _pathBase;
public:
    Servers(const string& hostname, const string& path, const string& token) : _token(token), _hostname(hostname), _connection(hostname), _pathBase(path) {
        std::cout << "Server url: https://" << hostname << '/' << path << "/servers"  << std::endl;
    };
    HTTPS& connection() {
        if (!_connection.isConnected())
            _connection.connect();
        return _connection;
    }
    void list() {
        std::cout << "Requesting server list: " << std::endl;
        HTTPS::Headers requestHeaders, responseHeaders;
        std::string body;
        requestHeaders.insert(HTTPS::Header("Host", _hostname));
        requestHeaders.insert(HTTPS::Header("X-Auth-Token", _token));
        requestHeaders.insert(HTTPS::Header("Accept", "application/xml"));
        for(HTTPS::Headers::const_iterator i=requestHeaders.begin(); i!=requestHeaders.end(); ++i) {
            std::cout << (*i).first << ": " << (*i).second << std::endl;
        }
        unsigned short responseCode = connection().request(_pathBase + "/servers", requestHeaders, responseHeaders, body);
        // print it out for now
        std::cout << body;
    }
};

} // namespace openstack

#endif // SERVER_HPP
