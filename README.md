# CSC 591 - A2

Goal: Build an R-Tree

This new repo currently only consists of copy+pasted code from assignment 1, except for name changes to files (and consequently, changes to some cmakelists.txt files)
to differentiate it from assignment 1. Made this to see if build instructions work with updated files.

## Build Instructions

Running this project will yield the assignment 1 submission code. This will be changed after I implement the r-tree code. 

```
mkdir build
cd build
cmake ../
make
./a2
```

## Build with Unit Tests

```
mkdir build
cd build
cmake ../ -DBUILD_TESTS=1
make
./test/unit_tests
```

## Extra info

An extra file called RTreeOrigin.cpp is also present in the repo, which contains the old RTree.cpp file that I had began writing. This will be removed shortly after I start implementing the R-Tree (and is currently here just for reference).