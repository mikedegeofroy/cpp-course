add_library(weather_report weather_report.cpp)
add_library(gui gui.cpp)

add_subdirectory(components)

target_link_libraries(weather_report
  PRIVATE weatherapi
  PRIVATE cityapi
  PRIVATE mapapi
  PRIVATE sqlitecache
  PRIVATE cpr::cpr
  PRIVATE nlohmann_json::nlohmann_json
  PRIVATE ftxui::screen
  PRIVATE ftxui::component
  PRIVATE ftxui::dom
)

target_link_libraries(gui
  PRIVATE weather_report
  PRIVATE components
  PRIVATE cpr::cpr
  PRIVATE nlohmann_json::nlohmann_json
  PRIVATE ftxui::screen
  PRIVATE ftxui::component
  PRIVATE ftxui::dom
)