CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

PROJECT (openstack_cpp_client)

ADD_DEFINITIONS(-Wall -Wextra)

SET(DEBUG true)

# Boost
MESSAGE(STATUS "Checking for Boost System. So that it works the same on all systems.")
find_package(Boost 1.41.0 REQUIRED COMPONENTS system)
if (NOT ${Boost_FOUND})
  MESSAGE(FATAL_ERROR "Couldn't find Boost libraries. On ubuntu: sudo apt-get install libboost-system-dev")
endif()
include_directories(BEFORE ${Boost_INCLUDE_DIRS})

# Boost ASIO headers
MESSAGE(STATUS "Checking for Boost ASIO headers. So we can stream our https connection")
find_file(ASIO_INCLUDE "boost/asio.hpp")
if ("${ASIO_INCLUDE}" STREQUAL "ASIO_INCLUDE-NOTFOUND")
  MESSAGE(FATAL_ERROR "Couldn't find Boost ASIO header files. On ubuntu: sudo apt-get install libasio-dev")
endif()

# OpenSSL 
MESSAGE(STATUS "Checking for OpenSSL, so we can make https:// connections")
find_package(OpenSSL REQUIRED) 
if (NOT ${OPENSSL_FOUND})
  MESSAGE(FATAL_ERROR "Couldn't find OpenSSL. On ubuntu: sudo apt-get install openssl-dev")
endif()
include_directories(BEFORE ${OPENSSL_INCLUDE_DIR})

# Xerces-c XML Parser
MESSAGE(STATUS "Checking for Xerces-c XML Parser")
find_library(xerces xerces-c) # Xerces for the XML parsing and generating
if ("${xerces}" STREQUAL "xerces_NOT_FOUND")
  MESSAGE(FATAL_ERROR "Couldn't find xserces-c library. On ubuntu: sudo apt-get install xbxerces-c-dev")
endif()

# XSD CXX
MESSAGE(STATUS "Checking for xsdcxx so we can parse and generate xml with the proper schemas")
find_file(XSD_INCLUDE "xsd/cxx/config.hxx")
if ("${XSD_INCLUDE}" STREQUAL "XSD_INCLUDE-NOTFOUND")
  MESSAGE(FATAL_ERROR "Couldn't find xsdcxx header files. On ubuntu: sudo apt-get install xsdcxx")
endif()

ADD_SUBDIRECTORY(xsd)

ADD_EXECUTABLE(test test.cpp)
TARGET_LINK_LIBRARIES(test ${Boost_SYSTEM_LIBRARY} ${OPENSSL_SSL_LIBRARIES} xsd)
