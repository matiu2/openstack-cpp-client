#include <iostream>
#include "openstack.hpp"
#include "model/ServerStub.hpp"

using std::cout;
using std::endl;
using openstack::Openstack;

int main(int argc, char **argv) {
    if (argc != 4)  {
        cout << "Usage: " << argv[0] << " username apikey url " << endl;
        return 1;
    }
    Openstack os(argv[1], argv[2], argv[3]);
	openstack::model::ServerStubMap stubs = os.servers().listServerStubs();
	for (auto serverPair : stubs) {
		openstack::model::ServerStub& stub = serverPair.second;
		cout << "Server:" << endl
				<< "  Id: " << stub.id() << endl
				<< "  Name:" << stub.name() << endl << endl;
	}
}
