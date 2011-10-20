#include "Servers.hpp"

namespace openstack {
namespace json {

Servers::Servers()  {
}

void Servers::readStubs(const StringType &json, model::ServerStubMap& stubs) {
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
        auto ptr = stubs.find(id);
        if (ptr == stubs.end()) {
            stubs.insert(std::make_pair(id, model::ServerStub(id, name)));
        } else {
            ptr->second.setName(name);
        }
    }
}

} // namespace openstack
} // namespace json
