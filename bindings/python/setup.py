#!/usr/bin/env python

"""setup.py file for SWIG wrapper around quad_key library.
Run with python setup.py build_ext --inplace
"""

import os


from distutils.core import setup, Extension


script_dir = os.path.dirname(os.path.realpath(__file__))

quad_keys_swig_cpp = os.path.join(script_dir, 'native')
quad_keys_swig_cpp = os.path.join(quad_keys_swig_cpp, 'quad_keys_python.cpp')

quad_keys_parent = os.path.join(script_dir, '..')
quad_keys_parent = os.path.join(quad_keys_parent, '..')

quad_keys_lib_dir = os.path.join(quad_keys_parent, 'build')
quad_keys_lib_dir = os.path.join(quad_keys_lib_dir, 'lib')

quad_key_module = Extension('_quad_key',
                            sources=[quad_keys_swig_cpp],
                            include_dirs=[quad_keys_parent,
                                          os.path.join(quad_keys_parent,
                                                       'include')],
                            extra_compile_args=['-std=c++11'],
                            libraries=['quad_key'],
                            library_dirs=[quad_keys_lib_dir],
                            runtime_library_dirs=[quad_keys_lib_dir])


setup(name='quad_key',
      version='0.1',
      author='Matthew Hoggan',
      description='A python wrapper around the quad_key library.',
      ext_modules=[quad_key_module],
      py_modules=['quad_key'])
