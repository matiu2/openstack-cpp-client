/*
 * =====================================================================================
 *
 *       Filename:  converters.hpp
 *
 *    Description:  Some handy dandy data converters, to make output of XML stuff easier
 *
 *        Version:  1.0
 *        Created:  02/08/11 12:22:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CONVERTERS_HPP
#define CONVERTERS_HPP

#include "../xml/server.hpp"

using openstack::xml::Server;
using openstack::xml::MetadataKey;
using openstack::xml::MetadataValue;
using openstack::xml::Metadata;

namespace openstack {


class MetadataMap : public std::map<openstack::xml::MetadataKey&, openstack::xml::MetadataValue&> {
private:
    Metadata& _holder;
public:
    typedef std::map<MetadataKey&, MetadataValue&> ParentType
    typedef pair<MetadataKey&, MetadataValue&> MetaDataPair
    MetadataMap(Metadata& holder) : ParentType(), _holder(holder) {}
    pair<iterator,bool> insert ( const value_type& x ) {
        pair<iterator,bool> result = ParentType::insert(x);
        if (result.second) {
            _holder.meta().push_back(iterator->first ... still working on it ..
    }
    iterator insert ( iterator position, const value_type& x );
    template <class InputIterator> void insert ( InputIterator first, InputIterator last );


};

/**
* @brief Returns a map with references to the actual
*
* @param metadata
*
* @return 
*/
MetaDataMap metadata2map(Server::MetadataOptional& metadata) {
    MetaDataMap result;
    if (metadata.present()) {
        const Metadata::MetaSequence& list = metadata->meta();
        for (Metadata::MetaConstIterator meta=list.begin(); meta!=list.end(); ++meta)
            map.push_back(MetaDataPair(meta->key(), *meta));
    }
    return result;
}

} // namespace openstack

#endif //  CONVERTERS_HPP
