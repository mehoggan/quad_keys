cmake_minimum_required(VERSION 3.0.2)

# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(LIB_EXTENSION "lib")
    set(LIB_PREFIX "")
    if(BUILD_SHARED_LIBS)
        set(ARGS_CMAKE "-DBUILD_SHARED_LIBS=ON")
    else()
        set(ARGS_CMAKE "-DBUILD_SHARED_LIBS=ON")
    endif()
else()
    set(LIB_PREFIX "lib")
    set(LIB_EXTENSION "a")
    if(BUILD_SHARED_LIBS)
        set(ARGS_CMAKE "")
    else()
        set(ARGS_CMAKE "")
    endif()
endif()

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL http://googletest.googlecode.com/files/gtest-1.7.0.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    CMAKE_ARGS ${ARGS_CMAKE}
    INSTALL_COMMAND "")
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)
ExternalProject_Get_Property(gtest source_dir binary_dir)
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set_target_properties(libgtest PROPERTIES
        IMPORTED_LOCATION "${binary_dir}/${LIB_PREFIX}gtest.${LIB_EXTENSION}"
        IMPORTED_LOCATION_DEBUG "${binary_dir}/Debug/${LIB_PREFIX}gtest.${LIB_EXTENSION}"
        IMPORTED_LOCATION_RELEASE "${binary_dir}/Release/${LIB_PREFIX}gtest.${LIB_EXTENSION}"
        IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")
else()
    set_target_properties(libgtest PROPERTIES
        IMPORTED_LOCATION "${binary_dir}/${LIB_PREFIX}gtest.${LIB_EXTENSION}"
        IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")
endif()

include_directories("${source_dir}/include")

# Download and install GoogleMock
ExternalProject_Add(
    gmock
    URL http://googlemock.googlecode.com/files/gmock-1.7.0.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gmock
    CMAKE_ARGS ${ARGS_CMAKE}
    INSTALL_COMMAND "")
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gmock)
ExternalProject_Get_Property(gmock source_dir binary_dir)
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set_target_properties(libgmock PROPERTIES
        IMPORTED_LOCATION "${binary_dir}/${LIB_PREFIX}gmock.${LIB_EXTENSION}"
        IMPORTED_LOCATION_DEBUG "${binary_dir}/Debug/${LIB_PREFIX}gmock.${LIB_EXTENSION}"
        IMPORTED_LOCATION_RELEASE "${binary_dir}/Release/${LIB_PREFIX}gmock.${LIB_EXTENSION}"
        IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")
else()
    set_target_properties(libgmock PROPERTIES
        IMPORTED_LOCATION "${binary_dir}/${LIB_PREFIX}gmock.${LIB_EXTENSION}"
        IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")
endif()

include_directories("${source_dir}/include")

