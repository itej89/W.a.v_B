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
include json-nlohmann/test/CMakeFiles/test-msgpack.dir/depend.make

# Include the progress variables for this target.
include json-nlohmann/test/CMakeFiles/test-msgpack.dir/progress.make

# Include the compile flags for this target's objects.
include json-nlohmann/test/CMakeFiles/test-msgpack.dir/flags.make

json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o: json-nlohmann/test/CMakeFiles/test-msgpack.dir/flags.make
json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o: json-nlohmann/test/src/unit-msgpack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tej/Documents/AniClientCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o"
	cd /home/tej/Documents/AniClientCpp/json-nlohmann/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o -c /home/tej/Documents/AniClientCpp/json-nlohmann/test/src/unit-msgpack.cpp

json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.i"
	cd /home/tej/Documents/AniClientCpp/json-nlohmann/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tej/Documents/AniClientCpp/json-nlohmann/test/src/unit-msgpack.cpp > CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.i

json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.s"
	cd /home/tej/Documents/AniClientCpp/json-nlohmann/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tej/Documents/AniClientCpp/json-nlohmann/test/src/unit-msgpack.cpp -o CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.s

json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o.requires:

.PHONY : json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o.requires

json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o.provides: json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o.requires
	$(MAKE) -f json-nlohmann/test/CMakeFiles/test-msgpack.dir/build.make json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o.provides.build
.PHONY : json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o.provides

json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o.provides.build: json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o


# Object files for target test-msgpack
test__msgpack_OBJECTS = \
"CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o"

# External object files for target test-msgpack
test__msgpack_EXTERNAL_OBJECTS = \
"/home/tej/Documents/AniClientCpp/json-nlohmann/test/CMakeFiles/doctest_main.dir/src/unit.cpp.o"

json-nlohmann/test/test-msgpack: json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o
json-nlohmann/test/test-msgpack: json-nlohmann/test/CMakeFiles/doctest_main.dir/src/unit.cpp.o
json-nlohmann/test/test-msgpack: json-nlohmann/test/CMakeFiles/test-msgpack.dir/build.make
json-nlohmann/test/test-msgpack: json-nlohmann/test/CMakeFiles/test-msgpack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tej/Documents/AniClientCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-msgpack"
	cd /home/tej/Documents/AniClientCpp/json-nlohmann/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-msgpack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
json-nlohmann/test/CMakeFiles/test-msgpack.dir/build: json-nlohmann/test/test-msgpack

.PHONY : json-nlohmann/test/CMakeFiles/test-msgpack.dir/build

json-nlohmann/test/CMakeFiles/test-msgpack.dir/requires: json-nlohmann/test/CMakeFiles/test-msgpack.dir/src/unit-msgpack.cpp.o.requires

.PHONY : json-nlohmann/test/CMakeFiles/test-msgpack.dir/requires

json-nlohmann/test/CMakeFiles/test-msgpack.dir/clean:
	cd /home/tej/Documents/AniClientCpp/json-nlohmann/test && $(CMAKE_COMMAND) -P CMakeFiles/test-msgpack.dir/cmake_clean.cmake
.PHONY : json-nlohmann/test/CMakeFiles/test-msgpack.dir/clean

json-nlohmann/test/CMakeFiles/test-msgpack.dir/depend:
	cd /home/tej/Documents/AniClientCpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tej/Documents/AniClientCpp /home/tej/Documents/AniClientCpp/json-nlohmann/test /home/tej/Documents/AniClientCpp /home/tej/Documents/AniClientCpp/json-nlohmann/test /home/tej/Documents/AniClientCpp/json-nlohmann/test/CMakeFiles/test-msgpack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : json-nlohmann/test/CMakeFiles/test-msgpack.dir/depend

