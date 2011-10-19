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

#include "services/https.hpp"
#include "net/Servers.hpp"
#include <boost/shared_ptr.hpp>
#include "lib/url.hpp"

using boost::shared_ptr;

using openstack::services::HTTPS;

namespace openstack {

class Openstack {
private:
    string _user;
    string _apikey;
    string _authUrl;
    std::pair<string,string> _authUrlParts; /// hostname, path
    string _authToken;
    string _cdnUrl;
    string _serverUrl;
    string _storageUrl;
    string _storageToken;

    HTTPS _connection;
    shared_ptr<net::Servers> _servers;

    string readHeader(const HTTPS::Headers& headers, const string& headerName);
    void auth();
    HTTPS& connection();
public:
    Openstack(const string& user, const string& apikey, const string& authUrl)
        : _user(user), _apikey(apikey), _authUrl(authUrl),
          _authUrlParts(getHostAndPath(authUrl)), _connection(_authUrlParts.first) {}
    shared_ptr<net::Servers> servers();
};

} // namespace openstack

#endif // OPENSTACK_HPP
