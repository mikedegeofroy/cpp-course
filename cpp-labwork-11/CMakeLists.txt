cmake_minimum_required(VERSION 3.12)

project(
    algorithms
    VERSION 1.0
    DESCRIPTION "Basic Algorithms"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)