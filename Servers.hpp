#pragma once
#ifndef OPENSTACK_SERVERS_HPP
#define OPENSTACK_SERVERS_HPP

#include "net/Servers.hpp"
#include "json/Servers.hpp"

namespace openstack {

class Servers {
private:
    net::Servers _net;
    json::Servers _parser;
public:
    Servers(const string& hostname, const string& path, const string& authToken) :
        _net(hostname, path, authToken, json::Servers::contentType()), _parser() {}
    //  Retreives a map of server stubs ordered by ID
    model::ServerStubMap listServerStubs();
};

} // namespace openstack

#endif // OPENSTACK_SERVERS_HPP
