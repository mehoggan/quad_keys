cmake_minimum_required(VERSION 3.0.2)
project(quad_keys)

option(BUILD_SHARED_LIBS "Build shared libraries over static library." ON)
option(QUAD_KEY_TESTS "Build unit tests." ON)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_MACOSX_RPATH 1)
endif()

include(${CMAKE_SOURCE_DIR}/CMake/c++11.cmake)

add_subdirectory(lib)

if(QUAD_KEY_TESTS)
  configure_file(${CMAKE_SOURCE_DIR}/CMakeLists.googletest.txt.in
    ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
  include(${CMAKE_SOURCE_DIR}/cmake/gtest.cmake)
  add_subdirectory(tests)
endif()
