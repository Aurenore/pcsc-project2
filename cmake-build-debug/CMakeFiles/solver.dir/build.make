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
include CMakeFiles/solver.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/solver.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/solver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/solver.dir/flags.make

CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.o: CMakeFiles/solver.dir/flags.make
CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.o: ../src/AbstractOdeSolver.cpp
CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.o: CMakeFiles/solver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.o -MF CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.o.d -o CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.o -c /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/AbstractOdeSolver.cpp

CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/AbstractOdeSolver.cpp > CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.i

CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/AbstractOdeSolver.cpp -o CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.s

CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.o: CMakeFiles/solver.dir/flags.make
CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.o: ../src/AbstractExplicitSolver.cpp
CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.o: CMakeFiles/solver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.o -MF CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.o.d -o CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.o -c /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/AbstractExplicitSolver.cpp

CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/AbstractExplicitSolver.cpp > CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.i

CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/AbstractExplicitSolver.cpp -o CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.s

CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.o: CMakeFiles/solver.dir/flags.make
CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.o: ../src/AdamsBashforthSolver.cpp
CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.o: CMakeFiles/solver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.o -MF CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.o.d -o CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.o -c /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/AdamsBashforthSolver.cpp

CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/AdamsBashforthSolver.cpp > CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.i

CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/AdamsBashforthSolver.cpp -o CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.s

# Object files for target solver
solver_OBJECTS = \
"CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.o" \
"CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.o" \
"CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.o"

# External object files for target solver
solver_EXTERNAL_OBJECTS =

libsolver.a: CMakeFiles/solver.dir/src/AbstractOdeSolver.cpp.o
libsolver.a: CMakeFiles/solver.dir/src/AbstractExplicitSolver.cpp.o
libsolver.a: CMakeFiles/solver.dir/src/AdamsBashforthSolver.cpp.o
libsolver.a: CMakeFiles/solver.dir/build.make
libsolver.a: CMakeFiles/solver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libsolver.a"
	$(CMAKE_COMMAND) -P CMakeFiles/solver.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/solver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/solver.dir/build: libsolver.a
.PHONY : CMakeFiles/solver.dir/build

CMakeFiles/solver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/solver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/solver.dir/clean

CMakeFiles/solver.dir/depend:
	cd /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2 /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2 /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles/solver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/solver.dir/depend

