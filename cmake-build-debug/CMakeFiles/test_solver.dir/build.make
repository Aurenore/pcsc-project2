# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/test_solver.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_solver.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_solver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_solver.dir/flags.make

CMakeFiles/test_solver.dir/test/test_solver.cc.o: CMakeFiles/test_solver.dir/flags.make
CMakeFiles/test_solver.dir/test/test_solver.cc.o: ../test/test_solver.cc
CMakeFiles/test_solver.dir/test/test_solver.cc.o: CMakeFiles/test_solver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_solver.dir/test/test_solver.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_solver.dir/test/test_solver.cc.o -MF CMakeFiles/test_solver.dir/test/test_solver.cc.o.d -o CMakeFiles/test_solver.dir/test/test_solver.cc.o -c /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/test/test_solver.cc

CMakeFiles/test_solver.dir/test/test_solver.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_solver.dir/test/test_solver.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/test/test_solver.cc > CMakeFiles/test_solver.dir/test/test_solver.cc.i

CMakeFiles/test_solver.dir/test/test_solver.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_solver.dir/test/test_solver.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/test/test_solver.cc -o CMakeFiles/test_solver.dir/test/test_solver.cc.s

# Object files for target test_solver
test_solver_OBJECTS = \
"CMakeFiles/test_solver.dir/test/test_solver.cc.o"

# External object files for target test_solver
test_solver_EXTERNAL_OBJECTS =

test_solver: CMakeFiles/test_solver.dir/test/test_solver.cc.o
test_solver: CMakeFiles/test_solver.dir/build.make
test_solver: lib/libgtest_maind.a
test_solver: lib/libgtestd.a
test_solver: libsolver.a
test_solver: CMakeFiles/test_solver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_solver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_solver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_solver.dir/build: test_solver
.PHONY : CMakeFiles/test_solver.dir/build

CMakeFiles/test_solver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_solver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_solver.dir/clean

CMakeFiles/test_solver.dir/depend:
	cd /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2 /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2 /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles/test_solver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_solver.dir/depend

