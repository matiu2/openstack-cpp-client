/*
 * =====================================================================================
 *
 *       Filename:  metadata.hpp
 *
 *    Description:  Some utility functions for reading meta data
 *
 *        Version:  1.0
 *        Created:  04/08/11 10:44:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "../xml/server.hpp"

namespace openstack {
namespace utils {

/**
* @brief Returns a changeable reference to a meta data value (basically a string) given a metadata key.
*
* @param server A reference to a server xml object
* @param key A string to search for
*
* @return A reference to the value, or a reference to a new Value if it doesn't exist
*/
xml::MetadataValue& getMetaDataValue(xml::Server& server, const string& key) {
    if (server.metadata().present()) {
        const Metadata::MetaSequence& list = server.metadata()->meta();
        for (Metadata::MetaConstIterator meta=server..begin(); meta!=list.end(); ++meta)
            if ((*i).key() == key)
                return (*i);
    // It doesn't exist .. lets add it
    server.metadata()->meta().push_back(xml::MetadataValue("", key));
}


} // namespace openstack
} // namespace utils
