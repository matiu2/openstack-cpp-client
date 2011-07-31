PROJECT (xsd)

# Builds all the .xsd files into a single static library
file(GLOB xsd_cpp_files *.cpp)
add_library(xsd STATIC ${xsd_cpp_files})
target_link_libraries(xsd ${xerces})
