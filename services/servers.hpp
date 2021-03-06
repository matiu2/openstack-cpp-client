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
#include <map>
#include "../xml/server.hpp"

using std::map;
using std::pair;
using std::auto_ptr;

namespace openstack {
namespace services {

class Servers {
private:
    typedef map<string, xml::Server*> Id2ServerPtrMap;   /// Used to point to a server that is part of a server list
    typedef pair<string, xml::Server*> Id2ServerPtrPair;
    typedef map<string, auto_ptr<xml::Server> > Id2ServerMap; /// Used to point to a server that was downloaded individually
    typedef pair<string, auto_ptr<xml::Server> > Id2ServerPair;
private:
    string _token;
    string _hostname;
    mutable HTTPS _connection;
    string _pathBase;
protected:
    // Cached values
    mutable std::auto_ptr< xml::Servers > _servers;
    mutable Id2ServerPtrMap _id2ServerPtrMap;
    mutable Id2ServerMap _id2ServerMap;
    /**
    * Downloads and parses something like this:
    * 
    * <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
    *  <servers xmlns="http://docs.rackspacecloud.com/servers/api/v1.0">
    *    <server id="1234" name="admin"/>
    *    <server id="563" name="stats"/>
    *    <server id="456546" name="web2"/>
    *    <server id="2345345" name="web1"/>
    *    <server id="234345" name="db1"/>
    *    <server id="34788" name="db2"/>
    *  </servers>"
    * 
    * Sets _servers.
    * Also clears and fills _id2ServerPtrMap.
    *
    * To use _servers:
    *   const xml::Servers::ServerSequence oc.servers().list().server();
    *   for(xml::Servers::ServerConstIterator server=list.begin();server!=list.end();++server)
    *       std::cout << "ID: " << server->id() << " - " << "Name: " << server->name() << std::endl;
    *
    * @param details if true, will get all the server details. If false, will get just the IDs and names
    *
    */
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
    void _fillId2ServerPtrMap(xml::Servers::ServerSequence& servers) {
        _id2ServerPtrMap.clear();
        for(Servers::ServerConstIterator server=servers.begin();server!=servers.end();++server)
            _id2ServerPtrMap.insert(Id2ServerPtrPair(server->id(), &server));
    }
public:
    Servers(const string& hostname, const string& path, const string& token) :
        _token(token), _hostname(hostname), _connection(hostname), _pathBase(path) {}
    HTTPS& connection() const {
        if (!_connection.isConnected())
            _connection.connect();
        return _connection;
    }
    /**
    * @brief Returns a reference to our cached vector of xml::Servers
    *
    * @param details if false the output will only have the server names
    * @param useCache if true and a cached value is available, it'll just use that and not connect to the service.
    *
    * @return a refernce to our cached vector of servers
    */
    xml::Servers::ServerSequence& list(bool details=true, bool useCache=true) {
        if ((!useCache) || (_servers.get() == 0))
            _list(details);
        return _servers->server();
    }
    const xml::Servers::ServerSequence& list(bool details=true, bool useCache=true) const {
        if ((!useCache) || (_servers.get() == 0))
            _list(details);
        return _servers->server();
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

#endif // SERVER_HPP
