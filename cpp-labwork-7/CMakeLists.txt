cmake_minimum_required(VERSION 3.12)

project(
    metadumper
    VERSION 1.0
    DESCRIPTION "mp3 metadata reader"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_subdirectory(src)
