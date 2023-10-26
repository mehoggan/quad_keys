# User Notes

# Developer Notes

## Build Dependencies

If you wish to clone all dependencies at once at the time of clone run:

```sh
> git clone git@github.com:mehoggan/quad_keys.git
```

## OSX System Setup

```sh
> brew install autoconf automake libtool autoconf-archive googletest
```

## Fedora DNF System Setup

```sh
> sudo dfn install -y ...
```

## Debian Apt System Setup

```sh
> sudo apt install -y git-all autoconf automake libtool autoconf-archive \
    libgtest-dev
```

## Build file generation and compiling library and executable Unix Systems

```sh
> autoreconf -i
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
//   "TestYAMLDagDeserializer.make_dag_vertices_not_list_of_obj"

// If you cannot find the logs then you can simply just run:
> ./test/gtest_libquad_keys
```
