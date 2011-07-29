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
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using openstack::Openstack;

int main(int argc, char* argv[]) {
  try {
      if (argc < 3) 
          cout << "Usage: " << argv[0] << " username apikey [hostname]" << endl;
     else {
         string hostname = "auth.api.rackspacecloud.com";
         if (argc >= 4)
             hostname = argv[3];
         Openstack os(argv[1], argv[2], hostname);
         os.checkConnection();
     }
  }
  catch (std::exception& e) {
    std::cout << "Exception: " << e.what() << "\n";
  }
  return 0;
}