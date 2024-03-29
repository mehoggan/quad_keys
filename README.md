# User Notes

# Developer Notes

## Build Dependencies

If you wish to clone all dependencies at once at the time of clone run:

```sh
> git clone git@github.com:mehoggan/quad_keys.git
```

## OSX System Setup

```sh
> brew install autoconf automake libtool autoconf-archive googletest gradle \
    python3 swig gradle
```

## Fedora DNF System Setup

```sh
> sudo dfn install -y ...
```

## Debian Apt System Setup

```sh
> sudo apt install -y git-all autoconf automake libtool autoconf-archive \
    libgtest-dev gradle python3
```

## Build file generation and compiling library and executable Unix Systems

```sh
> autoreconf -vis
> rm -rf ./build && mkdir -p ./build
> cd build/ && ../configure
> cd ../
> make -C build
```

## Running Tests

```sh
> make check

// If a test fails you can find that specific test in the build logs and then
// run:
> ./test/gtest_libquad_keys --gtest_filter=<name of test>
// example of gtest_filter is:
//   "BINGSYSTEM.is_root_key"
// If you cannot find the logs then you can simply just run:
> ./test/gtest_libquad_keys
```

## To build and run the java tests

```sh
> pushd ./bindings/java/quad_keys
> gradle build
> popd
```

## To build and run the python tests

```sh
> pushd ./bindings/python
> python setup.py build_ext --inplace
> cp _quad_keys*.so ./quad_keys/
> DYLD_LIBRARY_PATH=${PWD}/../../build/lib/.libs/ pytest
> popd
```

## To rebuild the swig bindings for Python3 and Java (for now)

```sh
# From the root of this project.
> find ./bindings/ -name "*.cpp" -exec rm {} \;
```
We do this because I could not get automake's `CLEANFILES` work correctly.
