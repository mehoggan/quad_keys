cmake_minimum_required(VERSION 3.0.2)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(SWIG swig-win)
else()
  set(SWIG swig)
endif()

set(SWIG_BASE ${CMAKE_CURRENT_SOURCE_DIR})

execute_process(COMMAND ${CMAKE_BINARY_DIR}/swig-build/${SWIG}
  -c++
  -java
  -package com.quad_key
  -I../include
  -I../
  -o ${SWIG_BASE}/java/quad_key/src/main/jni/java_quad_key.cpp
  -outdir ${SWIG_BASE}/java/quad_key/src/main/java/com/quad_key
  ${SWIG_BASE}/quad_key.swig
  WORKING_DIRECTORY ${SWIG_BASE}
  RESULT_VARIABLE swig_java_result
  OUTPUT_VARIABLE swig_java_output
  ERROR_VARIABLE swig_java_error)

message(STATUS "Swig java result = ${swig_java_result}")
message(STATUS "Swig java output = ${swig_java_output}")
message(STATUS "Swig java error = ${swig_java_error}")

execute_process(COMMAND ${CMAKE_BINARY_DIR}/swig-build/${SWIG}
  -c++
  -python
  -I../include
  -I../
  -o ${SWIG_BASE}/python/native/python_quad_key.cpp
  -outdir ${SWIG_BASE}/python/quad_key
  ${SWIG_BASE}/quad_key.swig
  WORKING_DIRECTORY ${SWIG_BASE}
  RESULT_VARIABLE swig_python_result
  OUTPUT_VARIABLE swig_python_output
  ERROR_VARIABLE swig_python_error)

message(STATUS "Swig python result = ${swig_python_result}")
message(STATUS "Swig python output = ${swig_python_output}")
message(STATUS "Swig python error = ${swig_python_error}")
