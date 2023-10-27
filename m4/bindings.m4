AC_DEFUN([FIND_JNI],
[$2=$(dirname $(find $1 -name "jni.h"))])

AC_DEFUN([FIND_JNI_MD],
[$2=$(dirname $(find $1 -name "jni_md.h"))])

AC_DEFUN([FIND_PYTHON_H],
[$1=$(dirname $(find $(dirname $(dirname $(which python3))) -name Python.h))])
