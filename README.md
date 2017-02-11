***BUILD libquad_key c++ OSX***
$ mkdir ./build/
$ pushd ./build/
$ export CXX=$(which clang++); export CC=$(which clang) && cmake ../
$ make -j 18
$ popd

***TEST libquad_key c++***
# First follow build steps.
$ pushd ./build/tests
$ ctest 'unit_test'
$ popd
$ popd

***Build and test libquad_key for java***
# Follow steps in BUILD for c++ for your specific platform. Then run:
$ pushd ./bindings/java/quad_key
$ gradle build
$ popd

***Build and test libqaud_key for python***
# Follow steps in BUILD for c++ for your specific platform. Then run:
# Copy libquad_key from build directory to the systems linker path.
$ pushd ./bindings/python
$ python setup.py build_ext --inplace
$ pytest
$ popd


