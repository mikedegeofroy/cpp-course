set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")

cmake_minimum_required(VERSION 3.12)

project(
    customallocator
    VERSION 1.0
    DESCRIPTION "Custom Allocator"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-O0")

add_subdirectory(lib)
add_subdirectory(src)