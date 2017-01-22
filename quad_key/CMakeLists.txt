cmake_minimum_required(VERSION 3.0.2)

include_directories(../)

set(SRC
    BingSystem.cpp
    BingSystem.h
    GeoCoordinate2d.cpp
    GeoCoordinate2d.h
    GeoCoordinateBoundingBox2d.cpp
    GeoCoordinateBoundingBox2d.h
    LatLongSystem.cpp
    LatLongSystem.h
    Macros.h
    MortonSystem.cpp
    MortonSystem.h
    NoneSystem.cpp
    NoneSystem.h
    OsGeoSystem.cpp
    OsGeoSystem.h
    QuadKeyTypes.cpp
    QuadKeyTypes.h
    QuadKey.cpp
    QuadKey.h
    System.cpp
    System.h
    UlpQnrSystem.cpp
    UlpQnrSystem.h
    Utils.cpp
    Utils.h)

if(QUADKEY_SWIG_LANGUAGE)
    include(${CMAKE_SOURCE_DIR}/CMake/swig.cmake)
    message("-- QUADKEY_SWIG_LANGUAGE=${QUADKEY_SWIG_LANGUAGE}")
    find_swig(
        HINT ${QUADKEY_SWIG_HINT}
        VERSION ${QUADKEY_SWIG_VERSION}
        URL ${QUADKEY_SWIG_URL})
    if(NOT SWIG_FOUND)
        message("-- Could not find installed version")
        message(FATAL_ERROR "--    ${QUADKEY_SWIG_VERSION} of swig")
    endif()
    generate_swig_stubs(
        CPP_SRC SRC
        SWIG_LANGUAGE ${QUADKEY_SWIG_LANGUAGE}
        SWIG_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Swig
        SWIG_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Swig)
    set(SRC "${src}") # src is set in generate_swig
endif()

if(BUILD_SHARED_LIBS)
    add_library(QuadKey SHARED ${SRC})
    add_definitions(-DQUADKEY_SHARED -DQUADKEY_EXPORTS)
else()
    add_library(QuadKey STATIC ${SRC})
    add_definitions(-DQUADKEY_STATIC)
endif()

if(QUADKEY_SWIG_LANGUAGE)
    add_swig_includes(
        TARGET QuadKey
        SWIG_LANGUAGE ${QUADKEY_SWIG_LANGUAGE})
    add_swig_dependency_checking(
        TARGET QuadKey
        SWIG_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Swig
        SWIG_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Swig
        SWIG_LANGUAGE ${QUADKEY_SWIG_LANGUAGE}
        INCLUDE_PATHS ${CMAKE_SOURCE_DIR}
        ADDITIONAL_SRC ${SRC})
    if("${QUADKEY_SWIG_LANGUAGE}" STREQUAL "csharp" AND
        ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        include_external_msproject(QuadKeyCSharp
            "${CMAKE_SOURCE_DIR}/Swig/QuadKeyCSharp.csproj")
        include_external_msproject(UnitTestCSharp
            "${CMAKE_SOURCE_DIR}/UnitTestCSharp/UnitTestCSharp.csproj")
        add_dependencies(QuadKeyCSharp QuadKey)
        add_dependencies(UnitTestCSharp QuadKeyCSharp)
    endif()
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    include(${CMAKE_SOURCE_DIR}/CMake/win32.cmake)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -fno-strict-aliasing")
endif()
