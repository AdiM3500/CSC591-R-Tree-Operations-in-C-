# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/aadit/Documents/CSC595-A1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/aadit/Documents/CSC595-A1/build

# Include any dependencies generated for this target.
include test/CMakeFiles/unit_tests.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/unit_tests.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/unit_tests.dir/flags.make

test/CMakeFiles/unit_tests.dir/unitTests.cpp.o: test/CMakeFiles/unit_tests.dir/flags.make
test/CMakeFiles/unit_tests.dir/unitTests.cpp.o: ../test/unitTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/aadit/Documents/CSC595-A1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/unit_tests.dir/unitTests.cpp.o"
	cd /mnt/c/Users/aadit/Documents/CSC595-A1/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_tests.dir/unitTests.cpp.o -c /mnt/c/Users/aadit/Documents/CSC595-A1/test/unitTests.cpp

test/CMakeFiles/unit_tests.dir/unitTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_tests.dir/unitTests.cpp.i"
	cd /mnt/c/Users/aadit/Documents/CSC595-A1/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/aadit/Documents/CSC595-A1/test/unitTests.cpp > CMakeFiles/unit_tests.dir/unitTests.cpp.i

test/CMakeFiles/unit_tests.dir/unitTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_tests.dir/unitTests.cpp.s"
	cd /mnt/c/Users/aadit/Documents/CSC595-A1/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/aadit/Documents/CSC595-A1/test/unitTests.cpp -o CMakeFiles/unit_tests.dir/unitTests.cpp.s

test/CMakeFiles/unit_tests.dir/btree/btree-tests.cpp.o: test/CMakeFiles/unit_tests.dir/flags.make
test/CMakeFiles/unit_tests.dir/btree/btree-tests.cpp.o: ../test/btree/btree-tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/aadit/Documents/CSC595-A1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/unit_tests.dir/btree/btree-tests.cpp.o"
	cd /mnt/c/Users/aadit/Documents/CSC595-A1/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_tests.dir/btree/btree-tests.cpp.o -c /mnt/c/Users/aadit/Documents/CSC595-A1/test/btree/btree-tests.cpp

test/CMakeFiles/unit_tests.dir/btree/btree-tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_tests.dir/btree/btree-tests.cpp.i"
	cd /mnt/c/Users/aadit/Documents/CSC595-A1/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/aadit/Documents/CSC595-A1/test/btree/btree-tests.cpp > CMakeFiles/unit_tests.dir/btree/btree-tests.cpp.i

test/CMakeFiles/unit_tests.dir/btree/btree-tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_tests.dir/btree/btree-tests.cpp.s"
	cd /mnt/c/Users/aadit/Documents/CSC595-A1/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/aadit/Documents/CSC595-A1/test/btree/btree-tests.cpp -o CMakeFiles/unit_tests.dir/btree/btree-tests.cpp.s

# Object files for target unit_tests
unit_tests_OBJECTS = \
"CMakeFiles/unit_tests.dir/unitTests.cpp.o" \
"CMakeFiles/unit_tests.dir/btree/btree-tests.cpp.o"

# External object files for target unit_tests
unit_tests_EXTERNAL_OBJECTS =

test/unit_tests: test/CMakeFiles/unit_tests.dir/unitTests.cpp.o
test/unit_tests: test/CMakeFiles/unit_tests.dir/btree/btree-tests.cpp.o
test/unit_tests: test/CMakeFiles/unit_tests.dir/build.make
test/unit_tests: src/btree/libbtree.a
test/unit_tests: test/CMakeFiles/unit_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/aadit/Documents/CSC595-A1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable unit_tests"
	cd /mnt/c/Users/aadit/Documents/CSC595-A1/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unit_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/unit_tests.dir/build: test/unit_tests

.PHONY : test/CMakeFiles/unit_tests.dir/build

test/CMakeFiles/unit_tests.dir/clean:
	cd /mnt/c/Users/aadit/Documents/CSC595-A1/build/test && $(CMAKE_COMMAND) -P CMakeFiles/unit_tests.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/unit_tests.dir/clean

test/CMakeFiles/unit_tests.dir/depend:
	cd /mnt/c/Users/aadit/Documents/CSC595-A1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/aadit/Documents/CSC595-A1 /mnt/c/Users/aadit/Documents/CSC595-A1/test /mnt/c/Users/aadit/Documents/CSC595-A1/build /mnt/c/Users/aadit/Documents/CSC595-A1/build/test /mnt/c/Users/aadit/Documents/CSC595-A1/build/test/CMakeFiles/unit_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/unit_tests.dir/depend

