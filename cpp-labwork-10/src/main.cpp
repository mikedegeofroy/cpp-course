#include <services/gui.h>

#include <iostream>
#include <nlohmann/json.hpp>

int main() {
  std::ifstream file("config.json");

  if (!file) {
    std::cout << "config.json file not found" << "\n";
    return 2;
  }

  json f = json::parse(file);

  if (f.empty()) {
    std::cout << "error while parsing json" << "\n";
  }

  const char* api_key_env = std::getenv("api_key");
  std::string api_key_config;

  std::string api_key;

  api_key = api_key_env;
  if (!api_key_env) {
    std::cout << "api_key not found in .env\n";

    api_key_config = f["api_key"].get<std::string>();
    if (api_key_config.empty()) {
      std::cout << "api_key not found in config.json\n";
      return 2;
    } 
  }
  api_key = api_key_config;


  std::vector<std::string> cities = f["cities"];

  auto gui = gui::UserInterface(api_key, cities);
  gui.Run();
}
