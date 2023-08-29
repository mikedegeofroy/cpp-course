cmake_minimum_required(VERSION 3.12)

project(
    sql
    VERSION 1.0
    DESCRIPTION "SQL Database"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(lib)