/*
 * =====================================================================================
 *
 *       Filename:  test_json.cpp
 *
 *    Description:  Tests JSON interpretation
 *
 *        Version:  1.0
 *        Created:  19/10/11 19:26:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE json_module

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include "../json/Servers.hpp"
#include <string>

using std::string;

namespace openstack {
namespace tests {

BOOST_AUTO_TEST_SUITE( json_suite );

BOOST_AUTO_TEST_CASE( json_server_stub_list ) {
    string json = "{\"servers\": [{\"id\":795837,\"name\":\"greg.archy\"},{\"id\":796534,\"name\":\"nater\"}]}";
    json::Servers reader;
    std::map<int,model::ServerStub> stubs;
	reader.readStubs(json, stubs);
    // Check the archy Slice
    auto archyI = stubs.find(795837);
    BOOST_REQUIRE_MESSAGE( archyI != stubs.end(), "Couldn't find the greg.arch server 795837" );
    model::ServerStub archy = archyI->second;
    BOOST_CHECK_EQUAL( archy.id(), 795837 );
    BOOST_CHECK_EQUAL( archy.name(), "greg.archy" );
    // Check the nater slice
    auto naterI = stubs.find(796534);
    BOOST_REQUIRE_MESSAGE( naterI != stubs.end(), "Couldn't find the nater server 796534" );
    model::ServerStub nater = naterI->second;
    BOOST_CHECK_EQUAL( nater.id(), 796534 );
    BOOST_CHECK_EQUAL( nater.name(), "nater" );
}

BOOST_AUTO_TEST_SUITE_END() // login_suite

} // namespace openstack
} // namespace tests
