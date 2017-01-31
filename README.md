***BUILD***
$ mkdir ./build/
$ pushd ./build/
$ cmake ../
$ make -j 18

***TEST***
# First follow build steps.
$ pushd tests
$ ctest 'unit_test'
$ popd
$ popd
