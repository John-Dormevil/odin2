# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/frederik_siepe/odinvst/company_name_generator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/frederik_siepe/odinvst/company_name_generator/build

# Include any dependencies generated for this target.
include CMakeFiles/helloDemo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/helloDemo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/helloDemo.dir/flags.make

CMakeFiles/helloDemo.dir/main.cpp.o: CMakeFiles/helloDemo.dir/flags.make
CMakeFiles/helloDemo.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/frederik_siepe/odinvst/company_name_generator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/helloDemo.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/helloDemo.dir/main.cpp.o -c /home/frederik_siepe/odinvst/company_name_generator/main.cpp

CMakeFiles/helloDemo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloDemo.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frederik_siepe/odinvst/company_name_generator/main.cpp > CMakeFiles/helloDemo.dir/main.cpp.i

CMakeFiles/helloDemo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloDemo.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frederik_siepe/odinvst/company_name_generator/main.cpp -o CMakeFiles/helloDemo.dir/main.cpp.s

CMakeFiles/helloDemo.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/helloDemo.dir/main.cpp.o.requires

CMakeFiles/helloDemo.dir/main.cpp.o.provides: CMakeFiles/helloDemo.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/helloDemo.dir/build.make CMakeFiles/helloDemo.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/helloDemo.dir/main.cpp.o.provides

CMakeFiles/helloDemo.dir/main.cpp.o.provides.build: CMakeFiles/helloDemo.dir/main.cpp.o


# Object files for target helloDemo
helloDemo_OBJECTS = \
"CMakeFiles/helloDemo.dir/main.cpp.o"

# External object files for target helloDemo
helloDemo_EXTERNAL_OBJECTS =

helloDemo: CMakeFiles/helloDemo.dir/main.cpp.o
helloDemo: CMakeFiles/helloDemo.dir/build.make
helloDemo: CMakeFiles/helloDemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/frederik_siepe/odinvst/company_name_generator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable helloDemo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/helloDemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/helloDemo.dir/build: helloDemo

.PHONY : CMakeFiles/helloDemo.dir/build

CMakeFiles/helloDemo.dir/requires: CMakeFiles/helloDemo.dir/main.cpp.o.requires

.PHONY : CMakeFiles/helloDemo.dir/requires

CMakeFiles/helloDemo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/helloDemo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/helloDemo.dir/clean

CMakeFiles/helloDemo.dir/depend:
	cd /home/frederik_siepe/odinvst/company_name_generator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/frederik_siepe/odinvst/company_name_generator /home/frederik_siepe/odinvst/company_name_generator /home/frederik_siepe/odinvst/company_name_generator/build /home/frederik_siepe/odinvst/company_name_generator/build /home/frederik_siepe/odinvst/company_name_generator/build/CMakeFiles/helloDemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/helloDemo.dir/depend

