cmake_minimum_required(VERSION 3.0.2)
project(quad_keys)

option(BUILD_SHARED_LIBS "Build shared libraries over static library." ON)
option(QUAD_KEY_TESTS "Build unit tests." ON)
option(QUAD_KEY_BINDINGS "Build all bindings for the native library." ON)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_MACOSX_RPATH 1)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/c++11.cmake)

add_subdirectory(lib)

if(QUAD_KEY_TESTS)
  message(STATUS "Going to build tests.")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.googletest.txt.in
    ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/gtest.cmake)
  add_subdirectory(tests)
endif()

if(QUAD_KEY_BINDINGS)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.swig.txt.in
    ${CMAKE_BINARY_DIR}/swig-download/CMakeLists.txt)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/swig.cmake)
  add_subdirectory(bindings)
endif()
