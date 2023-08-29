add_executable(main main.cpp)

target_link_libraries(main algorithms)
target_include_directories(main PUBLIC ${PROJECT_SOURCE_DIR})