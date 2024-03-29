AC_PREREQ([2.69])
AC_INIT([quad_keys], [1.0], [mehoggan@gmail.com])
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

# Conditionals
AC_CANONICAL_HOST()

# Detect the target system
build_linux=no
build_windows=no
build_mac=no
case "${host_os}" in
	linux*)
		build_linux=yes
    FIND_PYTHON_H(["/usr/include/python3.10"], [python_includes])
    AC_SUBST([python_includes])
		AC_CHECK_HEADERS([limits.h])
		AC_CHECK_LIB(m, sincos,
			[LIBS="-lm $LIBS" AC_DEFINE(HAVE_LIBM, 1, [Define if you have m.])],
			[AC_MSG_ERROR(
        [lib m is required - see https://www.gnu.org/software/libc/])])
    AC_PROG_CXX([g++])
    AC_MSG_RESULT(["Going to use $CXX as compiler in Linux environment."])
		;;
	darwin*)
		build_mac=yes
    FIND_PYTHON_H(["/Library/Frameworks/Python.framework/Versions/3.9/include/python3.9"],
      [python_includes])
    AC_SUBST([python_includes])
    AC_PROG_CXX([clang++])
    AC_MSG_RESULT(["Going to use $CXX as compiler in OSx environtment."])
		;;
	*)
		AC_MSG_ERROR(["OS $host_os is not supported"])
		;;
esac
AM_CONDITIONAL([LINUX], [test "$build_linux" = "yes"])
AM_CONDITIONAL([OSX], [test "$build_mac" = "yes"])
LT_INIT()

AX_CXX_COMPILE_STDCXX([17], [noext], [mandatory])
AC_CONFIG_SRCDIR([lib/quad_key.cpp])

AC_CONFIG_FILES([
  Makefile
  lib/Makefile
  test/Makefile
  bindings/Makefile
])

AC_SUBST(java_home, [$JAVA_HOME])
FIND_JNI([$java_home], [jni_home])
AC_SUBST([jni_home])
FIND_JNI_MD([$java_home], [jni_md_home])
AC_SUBST([jni_md_home])

AC_OUTPUT
