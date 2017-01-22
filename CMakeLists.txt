cmake_minimum_required(VERSION 3.0.2)
project(quad_keys)

include(${CMAKE_SOURCE_DIR}/CMake/c++11.cmake)

configure_file(${CMAKE_SOURCE_DIR}/CMakeLists.googletest.txt.in
	${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
include(${CMAKE_SOURCE_DIR}/cmake/gtest.cmake)

add_subdirectory(quad_key)
add_subdirectory(unit_test)
