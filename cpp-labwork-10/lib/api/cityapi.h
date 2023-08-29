#pragma once

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "../cache/sqlitecache.h"

#include <string>
#include <vector>

namespace city_api {

class Coordinates {
  private:
    float lattitude_;
    float longitude_;

  public:
    Coordinates() {};
    void Populate(float lat, float lon);
    float GetLattitude();
    float GetLongitude();
};

class City {
  private:
    std::string name_;
    std::string country_;
    size_t population_;
    bool is_capital_;
    cpr::Parameters parameters_;

  public:
    Coordinates coordinates;

    City() {}

    void Populate(std::string name, std::string country, size_t population, double lat, double lon, bool is_capital);

    std::string GetName();
    std::string GetCountry();
    size_t GetPopulation();
    bool IsCapital();
    cpr::Parameters GetParameters();

    City& AddParameter(const std::string& key, const std::string& value);
};

class CityApi {
  private:
    std::string api_key_;
    std::vector<City*> cities_;
    SQLiteCache* cache;

  public:
    CityApi(const std::string api_key) {
      api_key_ = api_key;
      cache = new SQLiteCache("cache.db");
    }

    City& AddCity() {
      City* new_city = new City();
      cities_.emplace_back(new_city);
      return *new_city;
    }
 
    std::vector<City> Get();

    ~CityApi() {
      for (auto it : cities_) {
        delete(it);
      }
      delete(cache);
    }

};

} // namespace city_api