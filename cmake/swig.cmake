macro(download_swig version url)
    message("-- Downloding Swig...")

    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        file(DOWNLOAD ${url}
            ${CMAKE_BINARY_DIR}/swig/swigwin-${version}.zip
            TIMEOUT 60 STATUS status INACTIVITY_TIMEOUT 60)

        message("-- Download status ${status}")

        message("-- Extracting ${CMAKE_BINARY_DIR}/swig/swigwin-${version}.zip...")
        execute_process(COMMAND ${CMAKE_COMMAND} -E
            tar xf ${CMAKE_BINARY_DIR}/swig/swigwin-${version}.zip
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/swig/)
    else()
        file(DOWNLOAD ${url}
            ${CMAKE_BINARY_DIR}/swig/swig-${version}.tar.gz
            TIMEOUT 30 STATUS status INACTIVITY_TIMEOUT 60)

        message("-- Download status ${status}")

        message("-- Extracting ${CMAKE_BINARY_DIR}/swig/swig-${version}.tar.gz...")
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

    if(NOT "" STREQUAL "${regex_match}" AND "${regex_match}" STREQUAL "${version}")
        message("-- First conditional in swig check swig_exe_path = ${swig_exe_path}.")
        set(SWIG_EXECUTABLE "${swig_exe_path}"
            CACHE FILEPATH "Path to were ${exe_name} is.")
        message("-- SWIG_EXECUTABLE(1) = ${SWIG_EXECUTABLE}")
        set(SWIG_FOUND_LOCAL true)
        set(SWIG_FOUND true CACHE BOOL "Global variable for if swig was configured.")
        set(SWIG_DIR "$ENV{SWIG_DIR}" CACHE PATH "Directory were ${exe_name} is.")
        set(SWIG_VERSION "${version}" CACHE STRING "Version of ${eve_name} is.")
    elseif("" STREQUAL "${version}")
        message("-- Second conditional in swig check swig_exe_path = ${swig_exe_path}.")
        set(SWIG_EXECUTABLE "${swig_exe_path}"
            CACHE FILEPATH "Path to were ${exe_name} is.")
        message("-- SWIG_EXECUTABLE(2) = ${SWIG_EXECUTABLE}")
        set(SWIG_FOUND_LOCAL true)
        set(SWIG_FOUND true CACHE BOOL "Global variable for if swig was configured.")
        set(SWIG_DIR "$ENV{SWIG_DIR}" CACHE PATH "Directory were ${exe_name} is.")
        set(SWIG_VERSION "${version}" CACHE STRING "Version of ${eve_name} is.")
    endif()
endmacro()

macro(swig_command_for_language language swig_include_list swig_output_cpp swig_file)
    message("-- swig_command_for_language called.")
    if("java" STREQUAL "${language}")
        get_filename_component(swig_output_cpp_dir "${swig_output_cpp}" DIRECTORY)
        get_filename_component(swig_output_cpp_nam "${swig_output_cpp}" NAME)
        set(swig_output_cpp_new
            "${swig_output_cpp_dir}/com/quadkey/${swig_output_cpp_nam}")
        add_custom_command(OUTPUT "${swig_output_cpp_new}"
            PRE_BUILD
            COMMAND "${SWIG_EXECUTABLE}"
            ARGS -c++ -${language} -package com.quadkey ${swig_include_list}
            -o "${swig_output_cpp_new}" "${swig_file}"
            MAIN_DEPENDENCY "${swig_file}"
            DEPENDS "${dependencies}")
        message("-- Swig executable is ${SWIG_EXECUTABLE}")
        execute_process(COMMAND ${SWIG_EXECUTABLE} -c++ -${language}
            -package com.quadkey
            -I${CMAKE_SOURCE_DIR} -o ${swig_output_cpp_new} ${swig_file}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
            ERROR_VARIABLE error)
        message("-- result of swig is=${result}")
    elseif("python" STREQUAL "${language}")
        add_custom_command(OUTPUT "${swig_output_cpp}"
            PRE_BUILD
            COMMAND "${SWIG_EXECUTABLE}"
            ARGS -c++ -${language} ${swig_include_list} -o "${swig_output_cpp}"
            "${swig_file}"
            MAIN_DEPENDENCY "${swig_file}"
            DEPENDS "${dependencies}")
        message("-- Swig executable is ${SWIG_EXECUTABLE}")
        execute_process(COMMAND ${SWIG_EXECUTABLE} -c++ -${language}
            -I${CMAKE_SOURCE_DIR}
            -o ${swig_output_cpp} ${swig_file}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
            ERROR_VARIABLE error)
        message("-- result of swig is=${result}")
    elseif("csharp" STREQUAL "${language}")
        add_custom_command(OUTPUT "${swig_output_cpp}"
            PRE_BUILD
            COMMAND "${SWIG_EXECUTABLE}"
            ARGS -c++ -${language} -namespace QuadKeys ${swig_include_list}
            -o "${swig_output_cpp}" "${swig_file}"
            MAIN_DEPENDENCY "${swig_file}"
            DEPENDS "${dependencies}")
        message("-- Swig executable is ${SWIG_EXECUTABLE}")
        execute_process(COMMAND ${SWIG_EXECUTABLE} -c++ -${language}
            -namespace QuadKeys
            -I${CMAKE_SOURCE_DIR}
            -o ${swig_output_cpp} ${swig_file}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
            ERROR_VARIABLE error)
        message("-- result of swig is=${result}")
    endif()
endmacro()

macro(swig_stubs_for_language output_dir language swig_files)
    if("java" STREQUAL "${language}")
        set(output_full_path "${output_dir}/src/main/${language}/com/quadkey")
    elseif("python" STREQUAL "${language}")
        set(output_full_path "${output_dir}/${language}")
    elseif("csharp" STREQUAL "${language}")
        set(output_full_path "${output_dir}/${language}")
    endif()

    file(REMOVE_RECURSE "${output_full_path}")
    file(MAKE_DIRECTORY "${output_full_path}/")
    foreach(swig_file ${swig_files})
        string(REPLACE ".swig" "_${language}.cpp" FILE_PATH ${swig_file})
        get_filename_component(OUTPUT_FILE ${FILE_PATH} NAME)
        set(OUTPUT_FILE "${OUTPUT_FILE}")
        set(out_file "${output_full_path}/${OUTPUT_FILE}")
        message("-- out_file=${out_file}")
        file(WRITE ${out_file} "")
        set(add_sources "${add_sources};${out_file}")
    endforeach()
endmacro()

#! ADD_SWIG_DEPENDENCY_CHECKING
# This function calls add_custom_command() to add a prebuild step that will
# set up a dependency between a swig filie in SWIG_SOURCE_FILE (.swig file) and
# a c++ header file, SWIG_API_HEADER (.h file) to a c++ swig generated file
# in SWIG_OUTPUT_DIR called SWIG_GENERATED_CPP. The custom_target will check
# for modifactions to SWIG_SOURCE_FILE or SWIG_API_HEADER, if there are changes
# it will invoke swig on the SWIG_SOURCE_FILE and generate SWIG_GENERATED_CPP.
#
# \TARGET[in] must be a target you want the custom command added to.
# \SWIG_SOURCE_DIR[in] must be an absolute path to where .swig file(s) exist
# \INCLUDE_PATHS[in] must be an absolute path(s) to where a corresponding .h
#  files exist that you want to be checked to regenerate swig output for.
# \SWIG_OUTPUT_DIR[in] the directory where you want swig to generate files
# \SWIG_LANGUAGE[in] the language for swig to generate
# \ADDITIONAL_SRC[in] any additional headers you want included.
# if this list has any .cpp files in it they will be ignored
function(ADD_SWIG_DEPENDENCY_CHECKING)
    set(options "")
    set(one_value_args TARGET SWIG_SOURCE_DIR SWIG_OUTPUT_DIR SWIG_LANGUAGE)
    set(multi_value_args INCLUDE_PATHS ADDITIONAL_SRC)

    cmake_parse_arguments(ADD_SWIG_DEPENDENCY_CHECKING "${options}"
        "${one_value_args}" "${multi_value_args}" ${ARGN})

    set(target ${ADD_SWIG_DEPENDENCY_CHECKING_TARGET})
    set(source_dir ${ADD_SWIG_DEPENDENCY_CHECKING_SWIG_SOURCE_DIR})
    set(output_dir ${ADD_SWIG_DEPENDENCY_CHECKING_SWIG_OUTPUT_DIR})
    set(language ${ADD_SWIG_DEPENDENCY_CHECKING_SWIG_LANGUAGE})

    if(NOT SWIG_FOUND)
        message(FATAL_ERROR "Swig executable not found by CMake.")
    endif()

    file(GLOB SWIG_FILES "${source_dir}/*.swig")

    string(REGEX REPLACE "[;]" " -I " swig_include_list
        "${ADD_SWIG_DEPENDENCY_CHECKING_INCLUDE_PATHS}")
    set(swig_include_list -I${swig_include_list})

    foreach(swig_file ${SWIG_FILES})
        string(REPLACE ".swig" "_${language}.cpp" swig_cpp_file ${swig_file})
        file(READ ${swig_file} swig_src)
        string(STRIP "${swig_src}" swig_src)

        set(include_part "#include[ ]*(\"|<)")
        set(path_part "(([A-Za-z0-9_]+)/)*")
        set(file_part "([A-Za-z0-9_]+)[.](h|hpp)")
        set(regex "(${include_part})(${path_part})(${file_part})")
        string(REGEX MATCHALL "${regex}" output ${swig_src})

        set(dependencies "")

        foreach(src ${ADD_SWIG_DEPENDENCY_CHECKING_ADDITIONAL_SRC})
            string(REGEX MATCHALL ".*[.](h|hpp)$" header "${src}")
            if(NOT "" STREQUAL "${header}")
                set(additional_dependency "${CMAKE_CURRENT_SOURCE_DIR}/${header}")
                set(dependencies "${dependencies};${additional_dependency}")
                unset(additional_dependency)
            endif()
        endforeach()

        list(APPEND all_dependencies "${dependencies}")

        get_filename_component(file_name ${swig_cpp_file} NAME)

        if("${QUADKEY_SWIG_LANGUAGE}" STREQUAL "java")
            set(swig_output_cpp "${output_dir}/src/main/${language}/${file_name}")
        else()
            set(swig_output_cpp "${output_dir}/${language}/${file_name}")
        endif()

        swig_command_for_language("${language}" "${swig_include_list}"
            "${swig_output_cpp}" "${swig_file}")
    endforeach()
    add_custom_target(SWIG_GENERATE_TARGET DEPENDS ${all_dependencies})
    add_dependencies(${target} SWIG_GENERATE_TARGET)
    if("${language}" STREQUAL "python")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
            find_package(PythonLibs REQUIRED)
            if("${PYTHONLIBS_FOUND}")
                message("-- Using ${PYTHON_LIBRARIES} for linking.")
                get_filename_component(pythonlibpath "${PYTHON_LIBRARIES}"
                    DIRECTORY)
                get_filename_component(pythonlib "${PYTHON_LIBRARIES}"
                    NAME)
                string(REPLACE ".lib" "" pythonlibname "${pythonlib}")
                message("-- Going to link against ${pythonlibname}")
                set_target_properties(${target} PROPERTIES LINK_FLAGS
                    "/LIBPATH:${pythonlibpath}")
                target_link_libraries(${target} "${pythonlibname}")
                return()
            endif()
        else()
            find_package(PythonLibs REQUIRED)
            message("-- Using ${PYTHON_LIBRARY} for linking.")
            target_link_libraries(${target} "${PYTHON_LIBRARY}")
        endif()
    endif()
endfunction()

#! ADD_SWIG_INCLUDES
#
# \TARGET[in] the target
# \SWIG_LANGUAGE[in] the swig language you want to generate. Used for determining
#  which headers to include
function(ADD_SWIG_INCLUDES)
    set(options "")
    set(one_value_args TARGET SWIG_LANGUAGE)
    set(multi_value_args "")

    cmake_parse_arguments(ADD_SWIG_INCLUDES "${options}" "${one_value_args}"
        "${multi_value_args}" ${ARGN})

    set(target ${ADD_SWIG_INCLUDES_TARGET})
    set(language ${ADD_SWIG_INCLUDES_SWIG_LANGUAGE})
    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        if("java" STREQUAL "${language}")
            if("" STREQUAL "$ENV{JAVA_HOME}")
                message(FATAL_ERROR "JAVA_HOME environment variable is empty.")
            endif()
            target_include_directories(${target} PUBLIC
                "$ENV{JAVA_HOME}/include"
                "$ENV{JAVA_HOME}/include/win32")
        elseif("python" STREQUAL "${language}")
            find_package(PythonLibs REQUIRED)
            if("${PYTHONLIBS_FOUND}")
                message("-- Using ${PYTHON_INCLUDE_DIR} for includes.")
                target_include_directories(${target} PUBLIC ${PYTHON_INCLUDE_DIR})
                return()
            endif()
        endif()
    else()
        if("java" STREQUAL "${language}")
            find_package(JNI REQUIRED)
            target_include_directories(${target} PUBLIC ${JNI_INCLUDE_DIRS})
        elseif("python" STREQUAL "${language}")
            find_package(PythonLibs REQUIRED)
            message("-- Using ${PYTHON_INCLUDE_DIR} for includes.")
            target_include_directories(${target} PUBLIC ${PYTHON_INCLUDE_DIR})
        elseif("csharp" STREQUAL "${language}")
            # No need to add includes here???
        endif()
    endif()
endfunction()

#! GENERATE_SWIG_STUBS
# \SWIG_LANGUAGE the swig language you want stubs generated for and added
#  to your target
# \SWIG_SOURCE_DIR[in] the location of your .swig files. Will not scan recursive
# \SWIG_OUTPUT_DIR[in] the location
# \CPP_SRC[in] a list to add the stubs to
# \src[out] SRC appended with stubs
function(GENERATE_SWIG_STUBS)
    set(options "")
    set(one_value_args SWIG_LANGUAGE SWIG_SOURCE_DIR SWIG_OUTPUT_DIR)
    set(multi_value_args CPP_SRC)

    cmake_parse_arguments(GENERATE_SWIG_STUBS "${options}" "${one_value_args}"
        "${multi_value_args}" ${ARGN})

    set(language ${GENERATE_SWIG_STUBS_SWIG_LANGUAGE})
    set(source_dir ${GENERATE_SWIG_STUBS_SWIG_SOURCE_DIR})
    set(output_dir ${GENERATE_SWIG_STUBS_SWIG_OUTPUT_DIR})
    set(tmp_src "${GENERATE_SWIG_STUBS_CPP_SRC}")

    file(GLOB SWIG_FILES "${source_dir}/*.swig")

    set(add_sources "")

    swig_stubs_for_language("${output_dir}" "${language}" "${SWIG_FILES}")
    set(src "${${tmp_src}};${add_sources}" PARENT_SCOPE)
endfunction()

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
