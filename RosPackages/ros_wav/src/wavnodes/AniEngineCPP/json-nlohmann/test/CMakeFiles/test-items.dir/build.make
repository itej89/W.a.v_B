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
CMAKE_SOURCE_DIR = /home/tej/Documents/AniClientCpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tej/Documents/AniClientCpp

# Include any dependencies generated for this target.
include json-nlohmann/test/CMakeFiles/test-items.dir/depend.make

# Include the progress variables for this target.
include json-nlohmann/test/CMakeFiles/test-items.dir/progress.make

# Include the compile flags for this target's objects.
include json-nlohmann/test/CMakeFiles/test-items.dir/flags.make

json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.o: json-nlohmann/test/CMakeFiles/test-items.dir/flags.make
json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.o: json-nlohmann/test/src/unit-items.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tej/Documents/AniClientCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.o"
	cd /home/tej/Documents/AniClientCpp/json-nlohmann/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-items.dir/src/unit-items.cpp.o -c /home/tej/Documents/AniClientCpp/json-nlohmann/test/src/unit-items.cpp

json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-items.dir/src/unit-items.cpp.i"
	cd /home/tej/Documents/AniClientCpp/json-nlohmann/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tej/Documents/AniClientCpp/json-nlohmann/test/src/unit-items.cpp > CMakeFiles/test-items.dir/src/unit-items.cpp.i

json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-items.dir/src/unit-items.cpp.s"
	cd /home/tej/Documents/AniClientCpp/json-nlohmann/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tej/Documents/AniClientCpp/json-nlohmann/test/src/unit-items.cpp -o CMakeFiles/test-items.dir/src/unit-items.cpp.s

json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.o.requires:

.PHONY : json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.o.requires

json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.o.provides: json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.o.requires
	$(MAKE) -f json-nlohmann/test/CMakeFiles/test-items.dir/build.make json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.o.provides.build
.PHONY : json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.o.provides

json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.o.provides.build: json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.o


# Object files for target test-items
test__items_OBJECTS = \
"CMakeFiles/test-items.dir/src/unit-items.cpp.o"

# External object files for target test-items
test__items_EXTERNAL_OBJECTS = \
"/home/tej/Documents/AniClientCpp/json-nlohmann/test/CMakeFiles/doctest_main.dir/src/unit.cpp.o"

json-nlohmann/test/test-items: json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.o
json-nlohmann/test/test-items: json-nlohmann/test/CMakeFiles/doctest_main.dir/src/unit.cpp.o
json-nlohmann/test/test-items: json-nlohmann/test/CMakeFiles/test-items.dir/build.make
json-nlohmann/test/test-items: json-nlohmann/test/CMakeFiles/test-items.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tej/Documents/AniClientCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-items"
	cd /home/tej/Documents/AniClientCpp/json-nlohmann/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-items.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
json-nlohmann/test/CMakeFiles/test-items.dir/build: json-nlohmann/test/test-items

.PHONY : json-nlohmann/test/CMakeFiles/test-items.dir/build

json-nlohmann/test/CMakeFiles/test-items.dir/requires: json-nlohmann/test/CMakeFiles/test-items.dir/src/unit-items.cpp.o.requires

.PHONY : json-nlohmann/test/CMakeFiles/test-items.dir/requires

json-nlohmann/test/CMakeFiles/test-items.dir/clean:
	cd /home/tej/Documents/AniClientCpp/json-nlohmann/test && $(CMAKE_COMMAND) -P CMakeFiles/test-items.dir/cmake_clean.cmake
.PHONY : json-nlohmann/test/CMakeFiles/test-items.dir/clean

json-nlohmann/test/CMakeFiles/test-items.dir/depend:
	cd /home/tej/Documents/AniClientCpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tej/Documents/AniClientCpp /home/tej/Documents/AniClientCpp/json-nlohmann/test /home/tej/Documents/AniClientCpp /home/tej/Documents/AniClientCpp/json-nlohmann/test /home/tej/Documents/AniClientCpp/json-nlohmann/test/CMakeFiles/test-items.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : json-nlohmann/test/CMakeFiles/test-items.dir/depend

