cmake_minimum_required(VERSION 3.0.2)

project(QuadKeys)

include(${CMAKE_SOURCE_DIR}/CMake/c++11.cmake)

include(${CMAKE_SOURCE_DIR}/CMake/gtest.cmake)

add_subdirectory(QuadKey)
add_subdirectory(UnitTest)
