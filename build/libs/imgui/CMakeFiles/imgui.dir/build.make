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

# Include any dependencies generated for this target.
include libs/imgui/CMakeFiles/imgui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include libs/imgui/CMakeFiles/imgui.dir/compiler_depend.make

# Include the progress variables for this target.
include libs/imgui/CMakeFiles/imgui.dir/progress.make

# Include the compile flags for this target's objects.
include libs/imgui/CMakeFiles/imgui.dir/flags.make

libs/imgui/CMakeFiles/imgui.dir/codegen:
.PHONY : libs/imgui/CMakeFiles/imgui.dir/codegen

libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/flags.make
libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/includes_CXX.rsp
libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.obj: E:/asu-seif/6)spring-2025-junior/CSE439\ -\ Design\ of\ Compilers/project/Python-Compiler/libs/imgui/backends/imgui_impl_glfw.cpp
libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.obj"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.obj -MF CMakeFiles\imgui.dir\backends\imgui_impl_glfw.cpp.obj.d -o CMakeFiles\imgui.dir\backends\imgui_impl_glfw.cpp.obj -c "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\backends\imgui_impl_glfw.cpp"

libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.i"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\backends\imgui_impl_glfw.cpp" > CMakeFiles\imgui.dir\backends\imgui_impl_glfw.cpp.i

libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.s"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\backends\imgui_impl_glfw.cpp" -o CMakeFiles\imgui.dir\backends\imgui_impl_glfw.cpp.s

libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/flags.make
libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/includes_CXX.rsp
libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.obj: E:/asu-seif/6)spring-2025-junior/CSE439\ -\ Design\ of\ Compilers/project/Python-Compiler/libs/imgui/backends/imgui_impl_opengl3.cpp
libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.obj"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.obj -MF CMakeFiles\imgui.dir\backends\imgui_impl_opengl3.cpp.obj.d -o CMakeFiles\imgui.dir\backends\imgui_impl_opengl3.cpp.obj -c "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\backends\imgui_impl_opengl3.cpp"

libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.i"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\backends\imgui_impl_opengl3.cpp" > CMakeFiles\imgui.dir\backends\imgui_impl_opengl3.cpp.i

libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.s"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\backends\imgui_impl_opengl3.cpp" -o CMakeFiles\imgui.dir\backends\imgui_impl_opengl3.cpp.s

libs/imgui/CMakeFiles/imgui.dir/imgui.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/flags.make
libs/imgui/CMakeFiles/imgui.dir/imgui.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/includes_CXX.rsp
libs/imgui/CMakeFiles/imgui.dir/imgui.cpp.obj: E:/asu-seif/6)spring-2025-junior/CSE439\ -\ Design\ of\ Compilers/project/Python-Compiler/libs/imgui/imgui.cpp
libs/imgui/CMakeFiles/imgui.dir/imgui.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object libs/imgui/CMakeFiles/imgui.dir/imgui.cpp.obj"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/imgui/CMakeFiles/imgui.dir/imgui.cpp.obj -MF CMakeFiles\imgui.dir\imgui.cpp.obj.d -o CMakeFiles\imgui.dir\imgui.cpp.obj -c "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui.cpp"

libs/imgui/CMakeFiles/imgui.dir/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui.cpp.i"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui.cpp" > CMakeFiles\imgui.dir\imgui.cpp.i

libs/imgui/CMakeFiles/imgui.dir/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui.cpp.s"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui.cpp" -o CMakeFiles\imgui.dir\imgui.cpp.s

libs/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/flags.make
libs/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/includes_CXX.rsp
libs/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.obj: E:/asu-seif/6)spring-2025-junior/CSE439\ -\ Design\ of\ Compilers/project/Python-Compiler/libs/imgui/imgui_demo.cpp
libs/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object libs/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.obj"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.obj -MF CMakeFiles\imgui.dir\imgui_demo.cpp.obj.d -o CMakeFiles\imgui.dir\imgui_demo.cpp.obj -c "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui_demo.cpp"

libs/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui_demo.cpp.i"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui_demo.cpp" > CMakeFiles\imgui.dir\imgui_demo.cpp.i

libs/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui_demo.cpp.s"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui_demo.cpp" -o CMakeFiles\imgui.dir\imgui_demo.cpp.s

libs/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/flags.make
libs/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/includes_CXX.rsp
libs/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.obj: E:/asu-seif/6)spring-2025-junior/CSE439\ -\ Design\ of\ Compilers/project/Python-Compiler/libs/imgui/imgui_draw.cpp
libs/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object libs/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.obj"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.obj -MF CMakeFiles\imgui.dir\imgui_draw.cpp.obj.d -o CMakeFiles\imgui.dir\imgui_draw.cpp.obj -c "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui_draw.cpp"

libs/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui_draw.cpp.i"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui_draw.cpp" > CMakeFiles\imgui.dir\imgui_draw.cpp.i

libs/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui_draw.cpp.s"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui_draw.cpp" -o CMakeFiles\imgui.dir\imgui_draw.cpp.s

libs/imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/flags.make
libs/imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/includes_CXX.rsp
libs/imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.obj: E:/asu-seif/6)spring-2025-junior/CSE439\ -\ Design\ of\ Compilers/project/Python-Compiler/libs/imgui/imgui_tables.cpp
libs/imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object libs/imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.obj"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.obj -MF CMakeFiles\imgui.dir\imgui_tables.cpp.obj.d -o CMakeFiles\imgui.dir\imgui_tables.cpp.obj -c "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui_tables.cpp"

libs/imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui_tables.cpp.i"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui_tables.cpp" > CMakeFiles\imgui.dir\imgui_tables.cpp.i

libs/imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui_tables.cpp.s"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui_tables.cpp" -o CMakeFiles\imgui.dir\imgui_tables.cpp.s

libs/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/flags.make
libs/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/includes_CXX.rsp
libs/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.obj: E:/asu-seif/6)spring-2025-junior/CSE439\ -\ Design\ of\ Compilers/project/Python-Compiler/libs/imgui/imgui_widgets.cpp
libs/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object libs/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.obj"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.obj -MF CMakeFiles\imgui.dir\imgui_widgets.cpp.obj.d -o CMakeFiles\imgui.dir\imgui_widgets.cpp.obj -c "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui_widgets.cpp"

libs/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui_widgets.cpp.i"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui_widgets.cpp" > CMakeFiles\imgui.dir\imgui_widgets.cpp.i

libs/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui_widgets.cpp.s"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui\imgui_widgets.cpp" -o CMakeFiles\imgui.dir\imgui_widgets.cpp.s

libs/imgui/CMakeFiles/imgui.dir/__/ImGuiFileDialog/ImGuiFileDialog.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/flags.make
libs/imgui/CMakeFiles/imgui.dir/__/ImGuiFileDialog/ImGuiFileDialog.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/includes_CXX.rsp
libs/imgui/CMakeFiles/imgui.dir/__/ImGuiFileDialog/ImGuiFileDialog.cpp.obj: E:/asu-seif/6)spring-2025-junior/CSE439\ -\ Design\ of\ Compilers/project/Python-Compiler/libs/ImGuiFileDialog/ImGuiFileDialog.cpp
libs/imgui/CMakeFiles/imgui.dir/__/ImGuiFileDialog/ImGuiFileDialog.cpp.obj: libs/imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object libs/imgui/CMakeFiles/imgui.dir/__/ImGuiFileDialog/ImGuiFileDialog.cpp.obj"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/imgui/CMakeFiles/imgui.dir/__/ImGuiFileDialog/ImGuiFileDialog.cpp.obj -MF CMakeFiles\imgui.dir\__\ImGuiFileDialog\ImGuiFileDialog.cpp.obj.d -o CMakeFiles\imgui.dir\__\ImGuiFileDialog\ImGuiFileDialog.cpp.obj -c "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\ImGuiFileDialog\ImGuiFileDialog.cpp"

libs/imgui/CMakeFiles/imgui.dir/__/ImGuiFileDialog/ImGuiFileDialog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/__/ImGuiFileDialog/ImGuiFileDialog.cpp.i"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\ImGuiFileDialog\ImGuiFileDialog.cpp" > CMakeFiles\imgui.dir\__\ImGuiFileDialog\ImGuiFileDialog.cpp.i

libs/imgui/CMakeFiles/imgui.dir/__/ImGuiFileDialog/ImGuiFileDialog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/__/ImGuiFileDialog/ImGuiFileDialog.cpp.s"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\ImGuiFileDialog\ImGuiFileDialog.cpp" -o CMakeFiles\imgui.dir\__\ImGuiFileDialog\ImGuiFileDialog.cpp.s

# Object files for target imgui
imgui_OBJECTS = \
"CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.obj" \
"CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.obj" \
"CMakeFiles/imgui.dir/imgui.cpp.obj" \
"CMakeFiles/imgui.dir/imgui_demo.cpp.obj" \
"CMakeFiles/imgui.dir/imgui_draw.cpp.obj" \
"CMakeFiles/imgui.dir/imgui_tables.cpp.obj" \
"CMakeFiles/imgui.dir/imgui_widgets.cpp.obj" \
"CMakeFiles/imgui.dir/__/ImGuiFileDialog/ImGuiFileDialog.cpp.obj"

# External object files for target imgui
imgui_EXTERNAL_OBJECTS =

libs/imgui/libimgui.a: libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.obj
libs/imgui/libimgui.a: libs/imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.obj
libs/imgui/libimgui.a: libs/imgui/CMakeFiles/imgui.dir/imgui.cpp.obj
libs/imgui/libimgui.a: libs/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.obj
libs/imgui/libimgui.a: libs/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.obj
libs/imgui/libimgui.a: libs/imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.obj
libs/imgui/libimgui.a: libs/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.obj
libs/imgui/libimgui.a: libs/imgui/CMakeFiles/imgui.dir/__/ImGuiFileDialog/ImGuiFileDialog.cpp.obj
libs/imgui/libimgui.a: libs/imgui/CMakeFiles/imgui.dir/build.make
libs/imgui/libimgui.a: libs/imgui/CMakeFiles/imgui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX static library libimgui.a"
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && $(CMAKE_COMMAND) -P CMakeFiles\imgui.dir\cmake_clean_target.cmake
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\imgui.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/imgui/CMakeFiles/imgui.dir/build: libs/imgui/libimgui.a
.PHONY : libs/imgui/CMakeFiles/imgui.dir/build

libs/imgui/CMakeFiles/imgui.dir/clean:
	cd /d "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" && $(CMAKE_COMMAND) -P CMakeFiles\imgui.dir\cmake_clean.cmake
.PHONY : libs/imgui/CMakeFiles/imgui.dir/clean

libs/imgui/CMakeFiles/imgui.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler" "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\libs\imgui" "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build" "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui" "E:\asu-seif\6)spring-2025-junior\CSE439 - Design of Compilers\project\Python-Compiler\build\libs\imgui\CMakeFiles\imgui.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : libs/imgui/CMakeFiles/imgui.dir/depend

