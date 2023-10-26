lib_LTLIBRARIES = libquad_keys_java.la
lib_LTLIBRARIES += libquad_keys_python.la

BINDINGS_DIR = $(abs_top_srcdir)/bindings

./python/native/quad_keys_python.cpp: Makefile
	swig \
  	-c++ \
  	-python \
  	-I$(abs_top_srcdir)/include \
  	-o $(BINDINGS_DIR)/python/native/quad_keys_python.cpp \
  	-outdir $(BINDINGS_DIR)/python/quad_keys \
  	$(BINDINGS_DIR)/quad_key.swig

./java/quad_keys/src/main/jni/quad_keys_java.cpp: Makefile
	swig \
  	-c++ \
  	-java \
  	-package com.quad_keys \
  	-I$(abs_top_srcdir)/include \
  	-o $(BINDINGS_DIR)/java/quad_keys/src/main/jni/quad_keys_java.cpp \
  	-outdir $(BINDINGS_DIR)/java/quad_keys/src/main/java/com/quad_keys \
  	$(BINDINGS_DIR)/quad_key.swig

libquad_keys_java_la_SOURCES = \
    ./java/quad_keys/src/main/jni/quad_keys_java.cpp

libquad_keys_python_la_SOURCES = \
    ./python/native/quad_keys_python.cpp

libquad_keys_java_la_CPPFLAGS = -Werror -Wall -pedantic \
    -I$(abs_top_srcdir)/include

libquad_keys_python_la_CPPFLAGS = -Werror -Wall -pedantic \
    -I$(abs_top_srcdir)/include

