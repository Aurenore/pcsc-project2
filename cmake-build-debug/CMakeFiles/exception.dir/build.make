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
include CMakeFiles/exception.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/exception.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/exception.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exception.dir/flags.make

CMakeFiles/exception.dir/src/Exception.cpp.o: CMakeFiles/exception.dir/flags.make
CMakeFiles/exception.dir/src/Exception.cpp.o: ../src/Exception.cpp
CMakeFiles/exception.dir/src/Exception.cpp.o: CMakeFiles/exception.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exception.dir/src/Exception.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exception.dir/src/Exception.cpp.o -MF CMakeFiles/exception.dir/src/Exception.cpp.o.d -o CMakeFiles/exception.dir/src/Exception.cpp.o -c /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/Exception.cpp

CMakeFiles/exception.dir/src/Exception.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exception.dir/src/Exception.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/Exception.cpp > CMakeFiles/exception.dir/src/Exception.cpp.i

CMakeFiles/exception.dir/src/Exception.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exception.dir/src/Exception.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/Exception.cpp -o CMakeFiles/exception.dir/src/Exception.cpp.s

CMakeFiles/exception.dir/src/FileNotOpenException.cpp.o: CMakeFiles/exception.dir/flags.make
CMakeFiles/exception.dir/src/FileNotOpenException.cpp.o: ../src/FileNotOpenException.cpp
CMakeFiles/exception.dir/src/FileNotOpenException.cpp.o: CMakeFiles/exception.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/exception.dir/src/FileNotOpenException.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exception.dir/src/FileNotOpenException.cpp.o -MF CMakeFiles/exception.dir/src/FileNotOpenException.cpp.o.d -o CMakeFiles/exception.dir/src/FileNotOpenException.cpp.o -c /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/FileNotOpenException.cpp

CMakeFiles/exception.dir/src/FileNotOpenException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exception.dir/src/FileNotOpenException.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/FileNotOpenException.cpp > CMakeFiles/exception.dir/src/FileNotOpenException.cpp.i

CMakeFiles/exception.dir/src/FileNotOpenException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exception.dir/src/FileNotOpenException.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/FileNotOpenException.cpp -o CMakeFiles/exception.dir/src/FileNotOpenException.cpp.s

CMakeFiles/exception.dir/src/UnsetOrderException.cpp.o: CMakeFiles/exception.dir/flags.make
CMakeFiles/exception.dir/src/UnsetOrderException.cpp.o: ../src/UnsetOrderException.cpp
CMakeFiles/exception.dir/src/UnsetOrderException.cpp.o: CMakeFiles/exception.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/exception.dir/src/UnsetOrderException.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exception.dir/src/UnsetOrderException.cpp.o -MF CMakeFiles/exception.dir/src/UnsetOrderException.cpp.o.d -o CMakeFiles/exception.dir/src/UnsetOrderException.cpp.o -c /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/UnsetOrderException.cpp

CMakeFiles/exception.dir/src/UnsetOrderException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exception.dir/src/UnsetOrderException.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/UnsetOrderException.cpp > CMakeFiles/exception.dir/src/UnsetOrderException.cpp.i

CMakeFiles/exception.dir/src/UnsetOrderException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exception.dir/src/UnsetOrderException.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/UnsetOrderException.cpp -o CMakeFiles/exception.dir/src/UnsetOrderException.cpp.s

CMakeFiles/exception.dir/src/SetOrderException.cpp.o: CMakeFiles/exception.dir/flags.make
CMakeFiles/exception.dir/src/SetOrderException.cpp.o: ../src/SetOrderException.cpp
CMakeFiles/exception.dir/src/SetOrderException.cpp.o: CMakeFiles/exception.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/exception.dir/src/SetOrderException.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exception.dir/src/SetOrderException.cpp.o -MF CMakeFiles/exception.dir/src/SetOrderException.cpp.o.d -o CMakeFiles/exception.dir/src/SetOrderException.cpp.o -c /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/SetOrderException.cpp

CMakeFiles/exception.dir/src/SetOrderException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exception.dir/src/SetOrderException.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/SetOrderException.cpp > CMakeFiles/exception.dir/src/SetOrderException.cpp.i

CMakeFiles/exception.dir/src/SetOrderException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exception.dir/src/SetOrderException.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/SetOrderException.cpp -o CMakeFiles/exception.dir/src/SetOrderException.cpp.s

CMakeFiles/exception.dir/src/OutOfRangeException.cpp.o: CMakeFiles/exception.dir/flags.make
CMakeFiles/exception.dir/src/OutOfRangeException.cpp.o: ../src/OutOfRangeException.cpp
CMakeFiles/exception.dir/src/OutOfRangeException.cpp.o: CMakeFiles/exception.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/exception.dir/src/OutOfRangeException.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exception.dir/src/OutOfRangeException.cpp.o -MF CMakeFiles/exception.dir/src/OutOfRangeException.cpp.o.d -o CMakeFiles/exception.dir/src/OutOfRangeException.cpp.o -c /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/OutOfRangeException.cpp

CMakeFiles/exception.dir/src/OutOfRangeException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exception.dir/src/OutOfRangeException.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/OutOfRangeException.cpp > CMakeFiles/exception.dir/src/OutOfRangeException.cpp.i

CMakeFiles/exception.dir/src/OutOfRangeException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exception.dir/src/OutOfRangeException.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/OutOfRangeException.cpp -o CMakeFiles/exception.dir/src/OutOfRangeException.cpp.s

CMakeFiles/exception.dir/src/UncoherentValueException.cpp.o: CMakeFiles/exception.dir/flags.make
CMakeFiles/exception.dir/src/UncoherentValueException.cpp.o: ../src/UncoherentValueException.cpp
CMakeFiles/exception.dir/src/UncoherentValueException.cpp.o: CMakeFiles/exception.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/exception.dir/src/UncoherentValueException.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exception.dir/src/UncoherentValueException.cpp.o -MF CMakeFiles/exception.dir/src/UncoherentValueException.cpp.o.d -o CMakeFiles/exception.dir/src/UncoherentValueException.cpp.o -c /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/UncoherentValueException.cpp

CMakeFiles/exception.dir/src/UncoherentValueException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exception.dir/src/UncoherentValueException.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/UncoherentValueException.cpp > CMakeFiles/exception.dir/src/UncoherentValueException.cpp.i

CMakeFiles/exception.dir/src/UncoherentValueException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exception.dir/src/UncoherentValueException.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/src/UncoherentValueException.cpp -o CMakeFiles/exception.dir/src/UncoherentValueException.cpp.s

# Object files for target exception
exception_OBJECTS = \
"CMakeFiles/exception.dir/src/Exception.cpp.o" \
"CMakeFiles/exception.dir/src/FileNotOpenException.cpp.o" \
"CMakeFiles/exception.dir/src/UnsetOrderException.cpp.o" \
"CMakeFiles/exception.dir/src/SetOrderException.cpp.o" \
"CMakeFiles/exception.dir/src/OutOfRangeException.cpp.o" \
"CMakeFiles/exception.dir/src/UncoherentValueException.cpp.o"

# External object files for target exception
exception_EXTERNAL_OBJECTS =

libexception.a: CMakeFiles/exception.dir/src/Exception.cpp.o
libexception.a: CMakeFiles/exception.dir/src/FileNotOpenException.cpp.o
libexception.a: CMakeFiles/exception.dir/src/UnsetOrderException.cpp.o
libexception.a: CMakeFiles/exception.dir/src/SetOrderException.cpp.o
libexception.a: CMakeFiles/exception.dir/src/OutOfRangeException.cpp.o
libexception.a: CMakeFiles/exception.dir/src/UncoherentValueException.cpp.o
libexception.a: CMakeFiles/exception.dir/build.make
libexception.a: CMakeFiles/exception.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libexception.a"
	$(CMAKE_COMMAND) -P CMakeFiles/exception.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exception.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exception.dir/build: libexception.a
.PHONY : CMakeFiles/exception.dir/build

CMakeFiles/exception.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exception.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exception.dir/clean

CMakeFiles/exception.dir/depend:
	cd /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2 /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2 /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug /mnt/c/Users/anyam/Desktop/MA3/PCSC/pcsc-project2/cmake-build-debug/CMakeFiles/exception.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exception.dir/depend

