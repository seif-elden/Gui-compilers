# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 4.0

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\msys64\ucrt64\bin\cmake.exe

# The command to remove a file.
RM = C:\msys64\ucrt64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build"

# Utility rule file for uninstall.

# Include any custom commands dependencies for this target.
include libs/glfw/CMakeFiles/uninstall.dir/compiler_depend.make

# Include the progress variables for this target.
include libs/glfw/CMakeFiles/uninstall.dir/progress.make

libs/glfw/CMakeFiles/uninstall:
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\glfw" && C:\msys64\ucrt64\bin\cmake.exe -P "E:/asu-seif/6)spring-2025-junior/CSE439 - Design of Compilers/project/Python-Compiler/build/libs/glfw/cmake_uninstall.cmake"

libs/glfw/CMakeFiles/uninstall.dir/codegen:
.PHONY : libs/glfw/CMakeFiles/uninstall.dir/codegen

uninstall: libs/glfw/CMakeFiles/uninstall
uninstall: libs/glfw/CMakeFiles/uninstall.dir/build.make
.PHONY : uninstall

# Rule to build all files generated by this target.
libs/glfw/CMakeFiles/uninstall.dir/build: uninstall
.PHONY : libs/glfw/CMakeFiles/uninstall.dir/build

libs/glfw/CMakeFiles/uninstall.dir/clean:
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\glfw" && $(CMAKE_COMMAND) -P CMakeFiles\uninstall.dir\cmake_clean.cmake
.PHONY : libs/glfw/CMakeFiles/uninstall.dir/clean

libs/glfw/CMakeFiles/uninstall.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler" "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\glfw" "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build" "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\glfw" "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\glfw\CMakeFiles\uninstall.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : libs/glfw/CMakeFiles/uninstall.dir/depend

