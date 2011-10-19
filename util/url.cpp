/*
 * =====================================================================================
 *
 *       Filename:  url.cpp
 *
 *    Description:  Provides the implemenation for parsing urls
 *
 *        Version:  1.0
 *        Created:  18/10/11 21:22:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "url.hpp"

namespace openstack {

std::pair<string, string> getHostAndPath(const string& url) {
    std::stringstream urlS(url);
    string schema, host, path;
    char slash;
    getline(urlS, schema, ':');
    urlS >> slash >> slash;
    getline(urlS, host, '/');
    getline(urlS, path, '?');
    return std::pair<string, string>(host, "/" + path);
}

} // namespace openstack
