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
CMAKE_SOURCE_DIR = /home/haswell/Projects/vsomeip-quic/usertest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/haswell/Projects/vsomeip-quic/usertest

# Include any dependencies generated for this target.
include CMakeFiles/quic-client-example.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/quic-client-example.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/quic-client-example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/quic-client-example.dir/flags.make

CMakeFiles/quic-client-example.dir/quic-client-example.cpp.o: CMakeFiles/quic-client-example.dir/flags.make
CMakeFiles/quic-client-example.dir/quic-client-example.cpp.o: quic-client-example.cpp
CMakeFiles/quic-client-example.dir/quic-client-example.cpp.o: CMakeFiles/quic-client-example.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/haswell/Projects/vsomeip-quic/usertest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/quic-client-example.dir/quic-client-example.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/quic-client-example.dir/quic-client-example.cpp.o -MF CMakeFiles/quic-client-example.dir/quic-client-example.cpp.o.d -o CMakeFiles/quic-client-example.dir/quic-client-example.cpp.o -c /home/haswell/Projects/vsomeip-quic/usertest/quic-client-example.cpp

CMakeFiles/quic-client-example.dir/quic-client-example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quic-client-example.dir/quic-client-example.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/haswell/Projects/vsomeip-quic/usertest/quic-client-example.cpp > CMakeFiles/quic-client-example.dir/quic-client-example.cpp.i

CMakeFiles/quic-client-example.dir/quic-client-example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quic-client-example.dir/quic-client-example.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/haswell/Projects/vsomeip-quic/usertest/quic-client-example.cpp -o CMakeFiles/quic-client-example.dir/quic-client-example.cpp.s

# Object files for target quic-client-example
quic__client__example_OBJECTS = \
"CMakeFiles/quic-client-example.dir/quic-client-example.cpp.o"

# External object files for target quic-client-example
quic__client__example_EXTERNAL_OBJECTS =

quic-client-example: CMakeFiles/quic-client-example.dir/quic-client-example.cpp.o
quic-client-example: CMakeFiles/quic-client-example.dir/build.make
quic-client-example: /home/haswell/Projects/vsomeip/build/libvsomeip3.so.3.4.10
quic-client-example: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
quic-client-example: /usr/lib/x86_64-linux-gnu/libboost_log.so.1.74.0
quic-client-example: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.74.0
quic-client-example: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.74.0
quic-client-example: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.74.0
quic-client-example: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.74.0
quic-client-example: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.74.0
quic-client-example: CMakeFiles/quic-client-example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/haswell/Projects/vsomeip-quic/usertest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable quic-client-example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/quic-client-example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/quic-client-example.dir/build: quic-client-example
.PHONY : CMakeFiles/quic-client-example.dir/build

CMakeFiles/quic-client-example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/quic-client-example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/quic-client-example.dir/clean

CMakeFiles/quic-client-example.dir/depend:
	cd /home/haswell/Projects/vsomeip-quic/usertest && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/haswell/Projects/vsomeip-quic/usertest /home/haswell/Projects/vsomeip-quic/usertest /home/haswell/Projects/vsomeip-quic/usertest /home/haswell/Projects/vsomeip-quic/usertest /home/haswell/Projects/vsomeip-quic/usertest/CMakeFiles/quic-client-example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/quic-client-example.dir/depend

