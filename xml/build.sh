#!/bin/sh
xsdcxx cxx-tree --generate-polymorphic --polymorphic-type-all --generate-inline --namespace-map http://docs.rackspacecloud.com/servers/api/v1.0=openstack::xml --type-naming ucc --function-naming lcc --hxx-suffix .hpp --cxx-suffix .cpp --ixx-suffix .ipp --generate-serialization --generate-doxygen xsds/*.xsd
