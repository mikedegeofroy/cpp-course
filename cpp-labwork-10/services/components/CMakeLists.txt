add_library(components components.cpp)

target_link_libraries(components
  PRIVATE ftxui::screen
  PRIVATE ftxui::component
  PRIVATE ftxui::dom
)