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
CMAKE_COMMAND = /snap/clion/193/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/193/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/persa/Desktop/Fase2/TP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/persa/Desktop/Fase2/TP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/gen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/gen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gen.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gen.dir/flags.make

CMakeFiles/gen.dir/gen/generator.cpp.o: CMakeFiles/gen.dir/flags.make
CMakeFiles/gen.dir/gen/generator.cpp.o: ../gen/generator.cpp
CMakeFiles/gen.dir/gen/generator.cpp.o: CMakeFiles/gen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/persa/Desktop/Fase2/TP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gen.dir/gen/generator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gen.dir/gen/generator.cpp.o -MF CMakeFiles/gen.dir/gen/generator.cpp.o.d -o CMakeFiles/gen.dir/gen/generator.cpp.o -c /home/persa/Desktop/Fase2/TP/gen/generator.cpp

CMakeFiles/gen.dir/gen/generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gen.dir/gen/generator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/persa/Desktop/Fase2/TP/gen/generator.cpp > CMakeFiles/gen.dir/gen/generator.cpp.i

CMakeFiles/gen.dir/gen/generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gen.dir/gen/generator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/persa/Desktop/Fase2/TP/gen/generator.cpp -o CMakeFiles/gen.dir/gen/generator.cpp.s

# Object files for target gen
gen_OBJECTS = \
"CMakeFiles/gen.dir/gen/generator.cpp.o"

# External object files for target gen
gen_EXTERNAL_OBJECTS =

gen: CMakeFiles/gen.dir/gen/generator.cpp.o
gen: CMakeFiles/gen.dir/build.make
gen: /usr/lib/x86_64-linux-gnu/libGL.so
gen: /usr/lib/x86_64-linux-gnu/libGLU.so
gen: /usr/lib/x86_64-linux-gnu/libglut.so
gen: /usr/lib/x86_64-linux-gnu/libXmu.so
gen: /usr/lib/x86_64-linux-gnu/libXi.so
gen: CMakeFiles/gen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/persa/Desktop/Fase2/TP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gen"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gen.dir/build: gen
.PHONY : CMakeFiles/gen.dir/build

CMakeFiles/gen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gen.dir/clean

CMakeFiles/gen.dir/depend:
	cd /home/persa/Desktop/Fase2/TP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/persa/Desktop/Fase2/TP /home/persa/Desktop/Fase2/TP /home/persa/Desktop/Fase2/TP/cmake-build-debug /home/persa/Desktop/Fase2/TP/cmake-build-debug /home/persa/Desktop/Fase2/TP/cmake-build-debug/CMakeFiles/gen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gen.dir/depend

