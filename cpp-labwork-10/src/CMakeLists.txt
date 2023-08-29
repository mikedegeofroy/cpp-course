add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
  PRIVATE gui
  PRIVATE weather_report
  PRIVATE mapapi
  PRIVATE sqlitecache
  PRIVATE cpr::cpr
  PRIVATE nlohmann_json::nlohmann_json
  PRIVATE ftxui::screen
  PRIVATE ftxui::component
  PRIVATE ftxui::dom
)
