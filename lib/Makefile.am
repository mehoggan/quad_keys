lib_LTLIBRARIES = libquad_keys.la

libquad_keys_la_CPPFLAGS = -Werror -Wall -pedantic \
	  -Wno-deprecated-declarations \
		-Wno-enum-constexpr-conversion \
		-Wno-sign-conversion \
		-Wno-shorten-64-to-32 \
    -I$(abs_top_srcdir)/include

libquad_keys_la_SOURCES = bing_system.cpp \
    geo_coordinate2d.cpp \
    geo_coordinate_bounding_box2d.cpp \
    lat_lon_system.cpp \
    morton_system.cpp \
    none_system.cpp \
    osgeo_system.cpp \
    quad_key.cpp \
    quad_key_types.cpp \
    system.cpp \
    ulp_qnr_system.cpp \
    utils.cpp


if LINUX
libquad_keys_la_LIBADD = $(INIT_LIBS) -lm
else
libquad_keys_la_LIBADD = $(INIT_LIBS)
endif
