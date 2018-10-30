cmake_minimum_required(VERSION 3.0.2)

include_directories(../)
include_directories(../include/)

set(SRC
  "bing_system.cpp"
  "geo_coordinate2d.cpp"
  "geo_coordinate_bounding_box2d.cpp"
  "lat_long_system.cpp"
  "morton_system.cpp"
  "none_system.cpp"
  "osgeo_system.cpp"
  "quad_key_types.cpp"
  "quad_key.cpp"
  "system.cpp"
  "s2_cell_system.cpp"
  "ulp_qnr_system.cpp"
  "utils.cpp")

if (BUILD_SHARED_LIBS)
  add_library(quad_key SHARED ${SRC})
  add_definitions(-DQUADKEY_SHARED -DQUADKEY_EXPORTS)
else()
  add_library(quad_key STATIC ${SRC})
  add_definitions(-DQUADKEY_STATIC)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/win32.cmake)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall \
    -fno-strict-aliasing")
endif()

install(TARGETS quad_key
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
