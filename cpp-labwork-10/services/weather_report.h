#include <ctime>
#include <string>

#include "../lib/api/cityapi.h"
#include "../lib/api/weatherapi.h"
#include "../lib/api/mapapi.h"

const int kWeekdays = 7;
const int kHoursInDay = 24;

struct DailyReport {
  DailyReport(weather_api::json weather, int day);

  int weathercode;
  std::vector<tm> time;
  std::vector<float> precipitation;
  std::vector<float> precipitation_probability;
  std::vector<float> temperature;
  std::vector<float> apparent_temperature;
  std::vector<float> visibility;
  std::vector<int> wind_direction;
  std::vector<float> wind_speed;
  tm date;
};

struct WeeklyReport {
  void Populate(weather_api::City city);
  void Clear();
  std::string city_name;
  std::string timestamp;
  std::vector<std::vector<std::string>> map;
  std::vector<DailyReport> daily_report;
  float latitude;
  float longitude;
};

class WeatherReport {
 public:
  WeatherReport(const std::string& api_key);

  std::vector<WeeklyReport*> Get(const std::vector<std::string>& cities);

  std::vector<WeeklyReport*> GetReports();

  ~WeatherReport();

 private:
  void UpdateData();

  std::vector<WeeklyReport*> reports_;
  city_api::CityApi* city_api_;
  weather_api::WeatherApi* weather_api_;
};