PROJECT (xsd)

# Builds all the .xsd files into a single static library

file(GLOB xsd_cpp_files *.cpp)

if (${UseXSDStaticLibrary})
    add_library(xsd STATIC ${xsd_cpp_files})
    target_link_libraries(xsd ${xerces})
else()
    set(xsd_cpp_files ${xsd_cpp_files} PARENT_SCOPE)
endif()
