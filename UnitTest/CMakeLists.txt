cmake_minimum_required(VERSION 3.0.2)

enable_testing()
add_test(NAME UnitTest COMMAND QuadKey_Unit_Test)

include_directories(../)

add_executable(UnitTest
    ./main.cpp
    ./TestBingSystem.cpp
    ./TestGeoCoordinate2d.cpp
    ./TestGeoCoordinateBoundingBox2d.cpp
    ./TestLatLongSystem.cpp
    ./TestMortonSystem.cpp
    ./TestOsGeoSystem.cpp
    ./TestQuadKey.cpp
    ./TestUlpQnrSystem.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    if(BUILD_SHARED_LIBS)
        add_custom_command(TARGET UnitTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/build/QuadKey/$<CONFIGURATION>"
            $<TARGET_FILE_DIR:UnitTest>/)
    endif()

    add_custom_command(TARGET UnitTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/build/gtest/src/gtest-build/$<CONFIGURATION>"
        $<TARGET_FILE_DIR:UnitTest>/)
    add_custom_command(TARGET UnitTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/build/gmock/src/gmock-build/$<CONFIGURATION>"
        $<TARGET_FILE_DIR:UnitTest>/)
endif()

include(${CMAKE_SOURCE_DIR}/CMake/win32.cmake)

target_link_libraries(UnitTest
    QuadKey
    libgtest
    libgmock)
target_link_libraries(UnitTest
    debug QuadKey
    libgtest
    libgmock)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if("${QUADKEY_SWIG_LANGUAGE}" STREQUAL "python")
       find_package(PythonLibs)
       if("${PYTHONLIBS_FOUND}")
            message("-- Using ${PYTHON_LIBRARY} for linking.")
            get_filename_component(pythonlibpath "${PYTHON_LIBRARIES}"
               DIRECTORY)
            get_filename_component(pythonlib "${PYTHON_LIBRARIES}"
                NAME)
            string(REPLACE ".lib" "" pythonlibname "${pythonlib}")
            message("-- Going to link against ${pythonlibname}")
            set_target_properties(UnitTest PROPERTIES LINK_FLAGS
                    "/LIBPATH:${pythonlibpath}")
           target_link_libraries(UnitTest "${pythonlibname}")
           return()
       endif()
    endif()
endif()

install(TARGETS UnitTest DESTINATION bin)
