project(tests)

ADD_DEFINITIONS( -fno-access-control ) # Helps us access private methods in functions

# For each test library copy and paste and change this
add_library(jsonTest SHARED test_json.cpp)
add_dependencies(jsonTest openstackServer)
TARGET_LINK_LIBRARIES(jsonTest openstackServer ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
SET(TEST_LIBS jsonTest)

add_executable(test_runner main.cpp)
add_dependencies(test_runner ${TEST_LIBS} userManagerTest)

TARGET_LINK_LIBRARIES(test_runner ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${TEST_LIBS})
