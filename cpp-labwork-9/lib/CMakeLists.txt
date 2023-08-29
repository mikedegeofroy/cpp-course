add_library(custom_allocator custom_allocator.cpp custom_allocator.h)
add_library(stack stack.cpp stack.h)

target_link_libraries(custom_allocator stack)