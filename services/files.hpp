/*
 * =====================================================================================
 *
 *       Filename:  files.hpp
 *
 *    Description:  Service for looking at cloud files
 *
 *        Version:  1.0
 *        Created:  15/08/11 12:09:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef FILES_HPP
#define FILES_HPP

#include <sstream>
#include <iostream>
#include <map>

using std::map;
using std::pair;
using std::auto_ptr;
using std::cout;
using std::endl;

namespace openstack {
namespace services {

class Files {
private:
    string _token;
    string _hostname;
    mutable HTTPS _connection;
    string _pathBase;
protected:
    void _list(bool details=false) const {
        // Do the request
        HTTPS::Headers requestHeaders, responseHeaders;
        std::stringstream body;
        requestHeaders.insert(HTTPS::Header("X-Auth-Token", _token));
        requestHeaders.insert(HTTPS::Header("Accept", "application/xml"));
        if (details) 
            connection().request(_pathBase + "/servers/detail", requestHeaders, responseHeaders, body);
        else
            connection().request(_pathBase + "/servers", requestHeaders, responseHeaders, body);
        // Parse the body and return the object
        body.seekp(std::stringstream::beg); // Go back to the beginning of our stream
        _servers = xml::servers(body, xml_schema::Flags::dont_validate);
        _fillId2ServerPtrMap(_servers->server());
    }
public:
    Files(const string& hostname, const string& path, const string& token) :
        _token(token), _hostname(hostname), _connection(hostname), _pathBase(path) {}
    HTTPS& connection() const {
        if (!_connection.isConnected())
            _connection.connect();
        return _connection;
    }
    /**
    * @brief Gets a refrence to a single Server given the server's ID
    *
    * @param serverId the ID to search for the server on
    * @param useCache If true will use the cached data if possible, rather than getting new info from API server
    *
    * @return A refernce to the server
    * @throws logic_error if it can't find the server
    */
    xml::Server& get(const string& serverId, bool useCache=true) {
        // If we have a cache just look it up
        if (useCache) {
            Id2ServerPtrMap::iterator iServer = _id2ServerPtrMap.find(serverId);
            if (iServer.second != 0)
                return *iServer.second;
            Id2ServerMap::itereator iServer2 = _id2ServerMap.find(serverId);
        }
        // Ask the api server for it
        auto_ptr< xml::Server > server = _server(serverId);
    }
};

} // namespace services
} // namespace openstack

#endif // FILES_HPP

