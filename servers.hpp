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
    * <?xml version="1.0" encoding="UTF-8" standalone="yes"?><servers xmlns="http://docs.rackspacecloud.com/servers/api/v1.0"><server id="795837" name="greg.archy"/><server id="796534" name="nater"/><server id="20098970" name="matiu.natty"/><server id="20098971" name="ross.natty"/><server id="20099000" name="ross.natty.2"/><server id="20111370" name="matiu.fedora"/></servers>"
    *
    * And returns an xml::servers element.
    */
    void list() {
        // Do the request
        HTTPS::Headers requestHeaders, responseHeaders;
        std::stringstream body;
        requestHeaders.insert(HTTPS::Header("Host", _hostname));
        requestHeaders.insert(HTTPS::Header("X-Auth-Token", _token));
        requestHeaders.insert(HTTPS::Header("Accept", "application/xml"));
        connection().request(_pathBase + "/servers", requestHeaders, responseHeaders, body);
        // Parse the body
        body.seekp(std::stringstream::beg); // Go back to the beginning of our stream
        std::auto_ptr<xml::Servers> servers = xml::servers(body, xml_schema::Flags::dont_validate);
        // Temporary debugging code
        std::cout << "Found Servers:" << std::endl;
        const xml::Servers::ServerSequence list = servers->server();
        for(xml::Servers::ServerConstIterator server=list.begin();server!=list.end();++server) {
            std::cout << "ID: " << server->id() << " - " << "Name: " << server->name() << std::endl;
        }
    }
};

} // namespace openstack

#endif // SERVER_HPP
