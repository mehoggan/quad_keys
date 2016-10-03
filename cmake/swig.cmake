macro(download_swig version url)
    message("-- Downloding Swig...")

    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        file(DOWNLOAD ${url}
            ${CMAKE_BINARY_DIR}/swig/swigwin-${version}.zip
            TIMEOUT 60 STATUS status INACTIVITY_TIMEOUT 60)

        message("-- Download status ${status}")

        message("-- Extracting "
            "${CMAKE_BINARY_DIR}/swig/swigwin-${version}.zip...")
        execute_process(COMMAND ${CMAKE_COMMAND} -E
            tar xf ${CMAKE_BINARY_DIR}/swig/swigwin-${version}.zip
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/swig/)
    else()
        file(DOWNLOAD ${url}
            ${CMAKE_BINARY_DIR}/swig/swig-${version}.tar.gz
            TIMEOUT 30 STATUS status INACTIVITY_TIMEOUT 60)

        message("-- Download status ${status}")

        message("-- Extracting ${CMAKE_BINARY_DIR}/swig/swig-"
            "${version}.tar.gz...")
        execute_process(COMMAND ${CMAKE_COMMAND} -E
            tar xf ${CMAKE_BINARY_DIR}/swig/swig-${version}.tar.gz
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/swig/)

        message("-- Building Swig...")
        execute_process(COMMAND ./configure
            --prefix=${CMAKE_BINARY_DIR}/swig/swig-${version}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/swig/swig-${version}/
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
            ERROR_VARIABLE error)
        execute_process(COMMAND make -j5
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/swig/swig-${version}/
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
            ERROR_VARIABLE error)

        message("-- Installing Swig...")
        file(MAKE_DIRECTORY
            "${CMAKE_BINARY_DIR}/swig/swig-${version}/share/swig/${version}")
        execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_BINARY_DIR}/swig/swig-${version}/Lib"
            "${CMAKE_BINARY_DIR}/swig/swig-${version}/share/swig/${version}")
    endif()
endmacro()

macro(verify_swig_version swig_exe_path)
    message("-- Testing swig executable = ${swig_exe_path}")
    execute_process(COMMAND ${swig_exe_path} -version
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error)
    message("-- Output from swig ${output}")
    string(REPLACE "\n" " " output "${output}")
    string(REPLACE "." "\\." regex "${version}")

    if(NOT "" STREQUAL "${regex}")
        string(REGEX MATCH ${regex} regex_match "${output}")
    endif()

    if(NOT "" STREQUAL "${regex_match}" AND "${regex_match}"
        STREQUAL "${version}")
        message("-- First conditional in swig check swig_exe_path = "
            "${swig_exe_path}.")
        set(SWIG_EXECUTABLE "${swig_exe_path}"
            CACHE FILEPATH "Path to were ${exe_name} is.")
        message("-- SWIG_EXECUTABLE(1) = ${SWIG_EXECUTABLE}")
        set(SWIG_FOUND_LOCAL true)
        set(SWIG_FOUND true CACHE BOOL
            "Global variable for if swig was configured.")
        set(SWIG_DIR "$ENV{SWIG_DIR}" CACHE PATH
            "Directory were ${exe_name} is.")
        set(SWIG_VERSION "${version}" CACHE STRING
            "Version of ${eve_name} is.")
    elseif("" STREQUAL "${version}")
        message("-- Second conditional in swig check swig_exe_path = "
            "${swig_exe_path}.")
        set(SWIG_EXECUTABLE "${swig_exe_path}"
            CACHE FILEPATH "Path to were ${exe_name} is.")
        message("-- SWIG_EXECUTABLE(2) = ${SWIG_EXECUTABLE}")
        set(SWIG_FOUND_LOCAL true)
        set(SWIG_FOUND true CACHE BOOL
            "Global variable for if swig was configured.")
        set(SWIG_DIR "$ENV{SWIG_DIR}" CACHE PATH
            "Directory were ${exe_name} is.")
        set(SWIG_VERSION "${version}" CACHE STRING
            "Version of ${eve_name} is.")
    endif()
endmacro()

#! FIND_SWIG
#
# This function will do its best to find a version of swig to build your
# your project with. If you pass it a URL it will use that URL and will
# install swig into your ${CMAKE_BINARY_DIR}/swig. If a URL is not provided
# then it will attempt to first look at the hint provided in the HINT
# parameter. Finally it will look at the ${SWIG_DIR} enivronment variable.
#
# \VERSION[in] the version for the swig executable that is expected. Only used
#  if set.
# \HINT[in] a absolute path to where you want this function to find swig in
# \URL[in] a url to use to download swig
# The following variables are added to CMake's cache.
#
# \SWIG_FOUND[cache] - set to true if SWIG is found
# \SWIG_DIR[cache] - the directory where swig is installed
# \SWIG_EXECUTABLE[cache] - the path to the swig executable
# \SWIG_VERSION[cache] - the version number of the swig executable
function(FIND_SWIG)
    set(options "")
    set(one_value_args VERSION HINT URL)
    set(multi_value_args "")

    cmake_parse_arguments(FIND_SWIG "${options}" "${one_value_args}"
        "${multi_value_args}" ${ARGN})

    message("-- FIND_SWIG called.")

    set(hint "${FIND_SWIG_HINT}")
    set(version "${FIND_SWIG_VERSION}")
    set(url "${FIND_SWIG_URL}")

    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        set(exe_name "swig.exe")
        set(swig_name "swigwin")
    else()
        set(exe_name "swig")
        set(swig_name "swig")
    endif()

    if(NOT "" STREQUAL "${url}")
        download_swig("${version}" ${url})
        set(swig_exe_path
            "${CMAKE_BINARY_DIR}/swig/${swig_name}-${version}/${exe_name}")
        string(REPLACE "\\" "/" swig_exe_path "${swig_exe_path}")
        message("-- swig_exe_path detected at = ${swig_exe_path}")
        verify_swig_version("${swig_exe_path}")
        return()
    endif()

    # This sets the variables above if it fails we try alternatives
    find_package(SWIG ${version} HINTS "${hint}" QUIET)
    if(SWIG_FOUND AND "${SWIG_VERSION}" STREQUAL "${version}")
        if(NOT "" STREQUAL "${version}")
            verify_swig_version("${swig_exe_path}")
            message("-- swig_exe_path detected at = ${swig_exe_path}")
        endif()
        return()
    endif()

    set(SWIG_FOUND_LOCAL false)

    if(NOT SWIG_FOUND OR NOT "${SWIG_VERSION}" STREQUAL "${version}")
        if(NOT "" STREQUAL "${hint}")
            set(swig_exe_path "${hint}/${exe_name}")
            string(REPLACE "\\" "/" swig_exe_path "${swig_exe_path}")
            verify_swig_version("${swig_exe_path}")
            message("-- swig_exe_path detected at = ${swig_exe_path}")
        endif()

        if(NOT "" STREQUAL "$ENV{SWIG_DIR}" AND NOT SWIG_FOUND_LOCAL)
            set(swig_exe_path "$ENV{SWIG_DIR}/${exe_name}")
            string(REPLACE "\\" "/" swig_exe_path "${swig_exe_path}")
            verify_swig_version("${swig_exe_path}")
            message("-- swig_exe_path detected at = ${swig_exe_path}")
        endif()
    endif()
endfunction()
