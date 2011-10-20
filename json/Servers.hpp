#pragma once

#include <string>
#include <stdexcept>
#include "../json_spirit/json_spirit_value.h"
#include "../json_spirit/json_spirit_reader.h"
#include "../model/ServerStub.hpp"

namespace openstack {
namespace json {

/** Provides a mechanism to translate a model::Servers instance to and from JSON
  */
class Servers {
public:
    typedef std::string StringType;
    typedef std::map<StringType, json_spirit::mValue> JSONObj;
    typedef json_spirit::mValue JSONValue;
    typedef std::vector<JSONValue> JSONArray;
public:
    Servers();
    /** Turns this:
        @code
            {"servers": [
                {"id":795837,"name":"greg.archy"},
                {"id":796534,"name":"nater"}
            ]}

        into a ServerStubMap
        @param json the json value to parse
        @param the dictionary of stubs to update. Existing entries will be found by ID and updated.
    **/
    void readStubs(const StringType &json, model::ServerStubMap& stubs);
    static std::string contentType() { return "application/json"; }
};



} // namespace openstack
} // namespace json
