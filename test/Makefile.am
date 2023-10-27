TESTS = gtest_libquad_keys
check_PROGRAMS = gtest_libquad_keys

gtest_libquad_keys_CPPFLAGS = -Werror -Wall -pedantic \
		-Wno-deprecated-declarations \
		-Wno-enum-constexpr-conversion \
	  -I$(abs_top_srcdir)/include \
	  -I$(abs_top_srcdir)/test/include

gtest_libquad_keys_SOURCES = main.cpp \
		test_bing_system.cpp \
		test_geo_coordinate2d.cpp \
		test_geo_coordinate_bounding_box2d.cpp \
		test_lat_long_system.cpp \
		test_morton_system.cpp \
		test_osgeo_system.cpp \
		test_quad_key.cpp \
		test_ulp_qnr_system.cpp

gtest_libquad_keys_LDADD = \
		$(abs_top_builddir)/lib/libquad_keys.la

gtest_libquad_keys_LDADD += -lgtest -lgmock

gtest_libquad_keys_LDADD += -lm
gtest_libquad_keys_LDFLAGS = -pthread

CLEANFILES = *.o
CLEANDIRS = deps/ .lib/
