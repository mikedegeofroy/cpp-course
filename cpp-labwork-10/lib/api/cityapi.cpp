#include "cityapi.h"

namespace city_api {

void Coordinates::Populate(float lattitude, float longitude) {
  lattitude_ = lattitude;
  longitude_ = longitude;
}

float Coordinates::GetLattitude() { return lattitude_; }

float Coordinates::GetLongitude() { return longitude_; }

void City::Populate(std::string name, std::string country, size_t population,
                    double lat, double lon, bool is_capital) {
  name_ = name;
  country_ = country;
  population_ = population;
  coordinates.Populate(lat, lon);
  is_capital_ = is_capital;
}

std::string City::GetName() { return name_; }

std::string City::GetCountry() { return country_; }

size_t City::GetPopulation() { return population_; }

bool City::IsCapital() { return is_capital_; }

cpr::Parameters City::GetParameters() { return parameters_; }

City& City::AddParameter(const std::string& key, const std::string& value) {
  parameters_.Add({key, value});
  return *this;
}

std::vector<City> CityApi::Get() {
  std::vector<City> response;

  for (auto city : cities_) {
    cpr::Parameters parameters = city->GetParameters();

    std::string cached_response =
        cache->get(parameters.GetContent(cpr::CurlHolder()));

    json data;

    if (cached_response.empty()) {
      cpr::Response r =
          cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
                   cpr::Header{{"X-Api-Key", api_key_}}, parameters);
      if (r.status_code != 200) {
        std::cerr << r.text << "\n";
        throw std::runtime_error("City API returned " +
                                 std::to_string(r.status_code) +
                                 " status code");
      }
      cache->put(parameters.GetContent(cpr::CurlHolder()), r.text);
      data = json::parse(r.text);
    } else {
      data = json::parse(cached_response);
    }

    for (auto it : data) {
      std::string city_name = it["name"].get<std::string>();
      std::string country = it["country"].get<std::string>();
      size_t population = it["population"].get<size_t>();
      float lon = it["longitude"].get<float>();
      float lat = it["latitude"].get<float>();
      bool is_capital = it["is_capital"].get<bool>();

      city->Populate(city_name, country, population, lat, lon, is_capital);
      response.emplace_back(*city);
    }
  }

  return response;
}

}  // namespace city_api