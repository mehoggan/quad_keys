cmake_minimum_required(VERSION 3.0.2)

find_program(valgrind REQUIRED)
set(CTEST_MEMORYCHECK_COMMAND "/usr/bin/valgrind") 
set(CTES_MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")
include(CTest)
enable_testing()

add_test(unit_test unit_test --report_level=no --log_level=all
  --output_format=xml --log_sink=${CMAKE_BINARY_DIR}/test_logs/${name}.xml)

include_directories(../include)
include_directories(../)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/win32.cmake)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall \
    -fno-strict-aliasing")
endif()

add_executable(unit_test
  ./main.cpp
  ./test_bing_system.cpp
  ./test_geo_coordinate2d.cpp
  ./test_geo_coordinate_bounding_box2d.cpp
  ./test_lat_long_system.cpp
  ./test_morton_system.cpp
  ./test_osgeo_system.cpp
  ./test_quad_key.cpp
  ./test_s2_cell_system.cpp
  ./test_ulp_qnr_system.cpp
)


target_link_libraries(unit_test
  quad_key
  gtest
  gtest_main
  gmock
  gmock_main)
target_link_libraries(unit_test
  debug quad_key
  gtest
  gtest_main
  gmock
  gmock_main)
