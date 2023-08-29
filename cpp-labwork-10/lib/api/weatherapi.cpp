#include "weatherapi.h"

namespace weather_api {

void City::Update() {
  cpr::Response r =
      cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
               cpr::Parameters{{"longitude", std::to_string(longitude_)},
                               {"latitude", std::to_string(latitude_)},
                               {"hourly", "temperature_2m"},
                               {"hourly", "apparent_temperature"},
                               {"hourly", "windspeed_10m"},
                               {"hourly", "winddirection_10m"},
                               {"hourly", "precipitation"},
                               {"hourly", "precipitation_probability"},
                               {"hourly", "visibility"},
                               {"daily", "weathercode"},
                               {"timezone", "GMT"}});
  if (r.status_code != 200) {
    std::cerr << r.text << "\n";
    throw std::runtime_error("Weather API returned " +
                             std::to_string(r.status_code) + " status code");
  }
  weather = json::parse(r.text);
}

void WeatherApi::Subscribe(const std::string& city_name, const float& latitude,
                           const float& longitude) {
  City* new_city = new City(city_name, latitude, longitude);
  cities_[city_name] = new_city;
}

City& WeatherApi::GetCity(const std::string& city_name) {
  return *cities_[city_name];
}

WeatherApi::WeatherApi() : running(true), thread(&WeatherApi::Updater, this) {}

void WeatherApi::Update() {
  for (auto [name, city] : cities_) {
    city->Update();
  }
  update_callback_();
}

void WeatherApi::StopUpdater() {
  std::unique_lock<std::mutex> lock(mutex);
  running = false;
  condition.notify_one();
}

void WeatherApi::Updater() {
  std::unique_lock<std::mutex> lock(mutex);
  while (running) {
    condition.wait_for(lock, std::chrono::minutes(5),
                       [this] { return !running; });
    if (running) Update();
  }
}

void WeatherApi::SetUpdateCallback(std::function<void()> callback) {
  update_callback_ = callback;
}

WeatherApi::~WeatherApi() {
  StopUpdater();
  if (thread.joinable()) thread.join();
  for (auto it : cities_) {
    delete (it.second);
  }
}

}  // namespace weather_api