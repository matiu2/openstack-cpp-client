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
#include "xsd/server.hpp"
#ifdef USE_INLINE_CODE
#include "xsd/server.ipp"
#endif

namespace openstack {

class Servers {
private:
    string _token;
    string _hostname;
    HTTPS _connection;
    string _pathBase;
public:
    Servers(const string& hostname, const string& path, const string& token) :
        _token(token), _hostname(hostname), _connection(hostname), _pathBase(path) {}
    HTTPS& connection() {
        if (!_connection.isConnected())
            _connection.connect();
        return _connection;
    }
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
    * To use the return value:
    *   const xml::Servers::ServerSequence oc.servers().list().server();
    *   for(xml::Servers::ServerConstIterator server=list.begin();server!=list.end();++server)
    *       std::cout << "ID: " << server->id() << " - " << "Name: " << server->name() << std::endl;
    *
    * @param details if true, will get all the server details. If false, will get just the IDs and names
    *
    * @return A smart pointer to an xml::Servers instance.
    */
    std::auto_ptr<xml::Servers> list(bool details=false) {
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
        return xml::servers(body, xml_schema::Flags::dont_validate);
    }
};

} // namespace openstack

#endif // SERVER_HPP
