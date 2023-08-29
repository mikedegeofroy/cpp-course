add_library(weatherapi weatherapi.cpp)
add_library(cityapi cityapi.cpp)
add_library(mapapi mapapi.cpp)

target_link_libraries(weatherapi
  PRIVATE cpr::cpr
  PRIVATE nlohmann_json::nlohmann_json
)

target_link_libraries(mapapi
  PRIVATE cpr::cpr
)

target_link_libraries(cityapi
  PRIVATE sqlitecache
  PRIVATE cpr::cpr
  PRIVATE nlohmann_json::nlohmann_json
)