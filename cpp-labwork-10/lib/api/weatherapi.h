#pragma once

#include <cpr/cpr.h>

#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <unordered_map>

namespace weather_api {

using json = nlohmann::json;

class City {
 private:
  float longitude_;
  float latitude_;
  std::string city_name_;

 public:
  json weather;

  City(const std::string& city_name, const float& latitude,
       const float& longitude)
      : city_name_(city_name), longitude_(longitude), latitude_(latitude) {
    Update();
  }

  float GetLongitude() { return longitude_; };
  float GetLatitude() { return latitude_; };

  void Update();

  std::string GetName() { return city_name_; }
};

class WeatherApi {
 private:
  std::function<void()> update_callback_ = []() {};
  ;
  std::unordered_map<std::string, City*> cities_;
  std::condition_variable condition;
  std::thread thread;
  std::mutex mutex;
  bool running;
  void Updater();
  void StopUpdater();

 public:
  WeatherApi();
  void SetUpdateCallback(std::function<void()> callback);
  void Subscribe(const std::string& city_name, const float& latitude,
                 const float& longitude);
  City& GetCity(const std::string& city_name);
  void Update();
  ~WeatherApi();
};

}  // namespace weather_api