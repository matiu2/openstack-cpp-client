#include <iostream>
#include "openstack.hpp"
#include "net/Servers.hpp"

using std::cout;
using std::endl;
using openstack::Openstack;

int main(int argc, char **argv) {
    if (argc != 4)  {
        cout << "Usage: " << argv[0] << " username apikey url " << endl;
        return 1;
    }
    Openstack os(argv[1], argv[2], argv[3]);
    cout << os.servers()->list() << endl;
}
