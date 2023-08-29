cmake_minimum_required(VERSION 3.12)

project(
    labwork5
    VERSION 1.0
    DESCRIPTION "C++ Year 2022 labwork5"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(lib)
add_subdirectory(bin)
add_subdirectory(tests)


enable_testing()
# add_subdirectory(tests)
