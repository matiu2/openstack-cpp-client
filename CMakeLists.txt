CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

PROJECT (openstack_cpp_client)

ADD_DEFINITIONS(-Wall -Wextra)

# Are we in debug mode
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    SET(DEBUG false)
else()
    SET(DEBUG true)
endif()

# Option to use the static library or not
OPTION(UseXSDStaticLibrary "If true, will compile XSD code to a static library and possibly reduce compilation time." ON)

# Boost
MESSAGE(STATUS "Checking for Boost System. So that it works the same on all systems.")
find_package(Boost 1.41.0 REQUIRED COMPONENTS system thread)
if (NOT ${Boost_FOUND})
  MESSAGE(FATAL_ERROR "Couldn't find Boost libraries. On ubuntu: sudo apt-get install libboost-system-dev libboost-thread-dev")
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

# Threads (for asio)
find_package(Threads REQUIRED)

ADD_EXECUTABLE(main main.cpp openstack.cpp lib/url.cpp net/Servers.cpp)
TARGET_LINK_LIBRARIES(main ${Boost_SYSTEM_LIBRARY} ${OPENSSL_SSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_THREAD_LIBRARY})
