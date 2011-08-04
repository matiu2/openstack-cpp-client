/*
 * =====================================================================================
 *
 *       Filename:  http.cpp
 *
 *    Description:  Experiment to see if we can do a http and https call to the API
 *
 *        Version:  1.0
 *        Created:  25/07/11 10:25:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "openstack.hpp"
#include "xml/server.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using openstack::Openstack;
using openstack::xml::Servers;
using openstack::xml::Server;
using openstack::xml::Metadata;
using openstack::xml::Addresses;
using openstack::xml::AddressList;


void printServers(const Servers::ServerSequence& servers) {
    std::cout << "Found Servers:" << std::endl;
    for(Servers::ServerConstIterator server=servers.begin();server!=servers.end();++server) {
       cout << "Server: " << endl
            << "  ID: " << server->id() << endl
            << "  name: " << server->name() << endl
            << "  metadata: " << endl;
        // Read metadata
        if (server->metadata().present()) {
            const Metadata::MetaSequence& list = server->metadata()->meta();
            for (Metadata::MetaConstIterator meta=list.begin(); meta!=list.end(); ++meta)
                cout << "    " << meta->key() << " = " << *meta << endl;
        }
        // Read addresses
        const Server::AddressesOptional& addresses = server->addresses();
        if (addresses.present()){ 
            const Addresses::PublicOptional& publicIPs = addresses->public_();
            if (publicIPs.present()) {
                cout << "  public IPs: " << endl;
                const AddressList::IpSequence& ips = publicIPs->ip();
                for (AddressList::IpConstIterator ip=ips.begin(); ip!=ips.end(); ++ip)
                    cout << "    " << ip->addr() << endl;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 3) 
            cout << "Usage: " << argv[0] << " username apikey [hostname]" << endl;
        else {
            string hostname = "auth.api.rackspacecloud.com";
            if (argc >= 4)
               hostname = argv[3];
            Openstack os(argv[1], argv[2], hostname);
            const Servers::ServerSequence& servers = os.servers()->list();
            printServers(servers);
        }
    } catch (std::exception& e) {
      std::cout << "Exception: " << e.what() << "\n";
    }
    return 0;
}
