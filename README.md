***BUILD***
$ mkdir ./build/
$ pushd ./build/
$ cmake ../
$ make -j 18

***TEST***
# First follow build steps.
$ ctest -D ExperimentalMemCheck
