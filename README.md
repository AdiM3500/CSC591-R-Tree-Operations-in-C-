# CSC 591 - Data Structure Assignment

This repository will contain the implementation of a two-dimensional R Tree in C++. It currently only contains this README file. I shall upload the source code and open a pull request as soon as I have the code somewhat working. Thank you! 

## Build Instructions

This project uses [CMake](https://cmake.org/) and [Catch2](https://github.com/catchorg/Catch2) as a build and unit test system, respectively. You are suggested to use an _out-of-source_ build by creating a separate subdirectory and invoking both `cmake` and `make` from there. For example, if you start in the top-level directory:

```
mkdir build
cd build
cmake ../
make
./a1
```

You can also build the sample unit tests as well with the `-BUILD_TESTS` flag to `cmake` as follows:
```
mkdir build
cd build
cmake ../ -DBUILD_TESTS=1
make
./test/unit_tests
```

## Dependencies

In order to run this code, you will need:

  * CMake (which comes pre-installed in most development environments)
  * Catch2 (which is a header-only library that has been shipped with this code and is subject to the Catch2 licensing)

