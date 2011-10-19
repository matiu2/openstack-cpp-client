/*
 * =====================================================================================
 *
 *       Filename:  json.hpp
 *
 *    Description:  High level functions for parsing JSON
 *
 *        Version:  1.0
 *        Created:  19/10/11 20:07:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#pragma once

#include <string>
#include <stdexcept>
#include "json_spirit/json_spirit_value.h"
#include "json_spirit/json_spirit_reader.h"
#include "model/ServerStub.hpp"

namespace openstack {

class JSONReader {
public:
    typedef std::string StringType;
    typedef std::map<StringType, json_spirit::mValue> JSONObj;
    typedef json_spirit::mValue JSONValue;
    typedef std::vector<JSONValue> JSONArray;
private:
    model::ServerStubMap _stubs;
public:
    /** Turns this:
        @code
            {"servers": [
                {"id":795837,"name":"greg.archy"},
                {"id":796534,"name":"nater"}
            ]}

        into a ServerStubMap
        @param json the json value to parse
    **/
    const model::ServerStubMap& readStubs(const StringType& json) {
        JSONValue value;
        if (!json_spirit::read(json, value)) {
            // If we fail to read it .. read it more carefully and throw an exception on the bad line
            // we don't call this straight off because it's 3-4 times slower and most times it should 
            // work anyway
            read_or_throw(json, value); 
        }
        // Make sure we have a json object
        JSONObj topLevel = value.get_obj();
        // Make sure the json object has a 'servers' property
        auto serversAttr = topLevel.find("servers");
        if (serversAttr == topLevel.end())
            throw std::runtime_error("Expected a 'servers' attribute: " + json);
        // Read the list of servers
        JSONArray serversInfo = serversAttr->second.get_array();
        for (auto serverVal : serversInfo) {
            auto serverObj = serverVal.get_obj();
            auto readVal = [&serverObj, &json](const StringType& attrName) -> JSONValue& {
                auto ptr = serverObj.find(attrName);
                if (ptr == serverObj.end())
                    throw std::runtime_error("Expected a '" + attrName + "' attribute: " + json);
                return ptr->second;
            };
            int id = readVal("id").get_int();
            StringType name = readVal("name").get_str();
            auto ptr = _stubs.find(id);
            if (ptr == _stubs.end()) {
                _stubs.insert(std::make_pair(id, new model::ServerStub(id, name)));
            } else {
                ptr->second->setName(name);
            }
        }
        return _stubs;
    }
};

}
