cmake_minimum_required(VERSION 4.0)
project(marching-squares LANGUAGES C CXX)

include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG 12.2.0
)
FetchContent_MakeAvailable(fmt)

include(FetchContent)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

add_executable(marching-squares
    src/main.cpp

    src/renderer/shader.cpp
)

target_compile_features(marching-squares PRIVATE cxx_std_20)

target_compile_options(marching-squares PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:
        -Wall -Wextra -Werror -Wshadow -Wconversion -Wsign-conversion
    >
)

target_link_libraries(marching-squares PRIVATE fmt::fmt glfw OpenGL::GL)

target_include_directories(marching-squares PRIVATE vendor)
