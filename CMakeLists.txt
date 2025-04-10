cmake_minimum_required(VERSION 3.15)

# Set compiler paths with full Windows paths
set(MSYS_PREFIX "C:/msys64/ucrt64")
set(CMAKE_C_COMPILER "${MSYS_PREFIX}/bin/gcc.exe" CACHE PATH "C compiler" FORCE)
set(CMAKE_CXX_COMPILER "${MSYS_PREFIX}/bin/g++.exe" CACHE PATH "C++ compiler" FORCE)
set(CMAKE_MAKE_PROGRAM "${MSYS_PREFIX}/bin/mingw32-make.exe" CACHE PATH "Make program" FORCE)

# Must be set before project()
set(CMAKE_SYSTEM_NAME Windows)

project(python_compiler LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Verify compiler
if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "This project requires the GNU g++ compiler")
endif()

message(STATUS "Using C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Using C++ compiler: ${CMAKE_CXX_COMPILER}")

# GLFW
add_subdirectory(libs/glfw)
include_directories(libs/glfw/include)

# ImGui with FileDialog
add_subdirectory(libs/imgui)

# Main executable
add_executable(compiler_gui
    src/gui.cpp
    src/main.cpp
    src/utils.cpp
)

# Include directories
target_include_directories(compiler_gui PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/libs/imgui
    ${CMAKE_SOURCE_DIR}/libs/imgui/backends
    ${CMAKE_SOURCE_DIR}/libs/ImGuiFileDialog  # Add FileDialog includes
)

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Link libraries
target_link_libraries(compiler_gui
    glfw
    imgui
    ${OPENGL_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

# Windows-specific libraries
if(WIN32)
    target_link_libraries(compiler_gui
        opengl32
        gdi32
    )
endif()

# Linux-specific libraries
if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(compiler_gui
        X11
        Xrandr
        Xi
        Xcursor
    )
endif()

message(STATUS "Build configuration complete")
message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")