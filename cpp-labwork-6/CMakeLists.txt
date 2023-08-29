cmake_minimum_required(VERSION 3.0.0)
project(lab6 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

link_directories(lib)

add_subdirectory(lib)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)
