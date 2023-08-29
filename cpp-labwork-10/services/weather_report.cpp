#include "weather_report.h"

DailyReport::DailyReport(weather_api::json weather, int day) {
  int start_index = day * kHoursInDay;
  int end_index = (day + 1) * kHoursInDay - 1;

  weathercode = weather["daily"]["weathercode"][day];

  std::string date_buffer = weather["daily"]["time"][day];
  strptime(date_buffer.c_str(), "%Y-%m-%d", &date);

  for (int i = start_index; i <= end_index; ++i) {
    tm timestamp;
    date_buffer = weather["hourly"]["time"][i];
    strptime(date_buffer.c_str(), "%Y-%m-%dT%H:%M", &timestamp);
    time.emplace_back(timestamp);
  }

  temperature = {&weather["hourly"]["temperature_2m"][start_index],
                 &weather["hourly"]["temperature_2m"][end_index]};

  apparent_temperature = {
      &weather["hourly"]["apparent_temperature"][start_index],
      &weather["hourly"]["apparent_temperature"][end_index]};

  precipitation = {&weather["hourly"]["precipitation"][start_index],
                   &weather["hourly"]["precipitation"][end_index]};

  precipitation_probability = {
      &weather["hourly"]["precipitation_probability"][start_index],
      &weather["hourly"]["precipitation_probability"][end_index]};

  visibility = {&weather["hourly"]["visibility"][start_index],
                &weather["hourly"]["visibility"][end_index]};

  wind_direction = {&weather["hourly"]["winddirection_10m"][start_index],
                    &weather["hourly"]["winddirection_10m"][end_index]};
  wind_speed = {&weather["hourly"]["windspeed_10m"][start_index],
                &weather["hourly"]["windspeed_10m"][end_index]};
}

void WeeklyReport::Populate(weather_api::City city) {
  Clear();
  latitude = city.GetLatitude();
  longitude = city.GetLongitude();
  map = GetMap(latitude, longitude);
  city_name = city.GetName();
  for (int i = 0; i < kWeekdays; ++i) {
    DailyReport day(city.weather, i);
    daily_report.push_back(day);
  }
  std::time_t t = std::time(0);
  std::tm now = *localtime(&t);
  char buf[80];
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &now);
  timestamp = buf;
  std::cout << timestamp << ": updated " << city.GetName() <<"\n";
}

void WeeklyReport::Clear() {
  city_name = "";
  timestamp = "";
  map.clear();
  daily_report.clear();
  latitude = 0;
  longitude = 0;
}

WeatherReport::WeatherReport(const std::string& api_key) {
  city_api_ = new city_api::CityApi(api_key);
  weather_api_ = new weather_api::WeatherApi();
  weather_api_->SetUpdateCallback([&]() { this->UpdateData(); });
}

std::vector<WeeklyReport*> WeatherReport::GetReports() { return reports_; }

std::vector<WeeklyReport*> WeatherReport::Get(const std::vector<std::string>& cities) {
  for (auto& city_name : cities) {
    city_api::City& new_city = city_api_->AddCity();
    new_city.AddParameter("name", city_name);
  }
  auto city_data = city_api_->Get();

  for (auto& city : city_data) {
    weather_api_->Subscribe(city.GetName(),
                            city.coordinates.GetLattitude(),
                            city.coordinates.GetLongitude());
  }
  weather_api_->Update();

  for (auto& city : city_data) {
    weather_api::City result = weather_api_->GetCity(city.GetName());
    WeeklyReport* report = new WeeklyReport;
    report->Populate(result);
    reports_.emplace_back(report);
  }

  return reports_;
}

WeatherReport::~WeatherReport() {
  delete (city_api_);
  delete (weather_api_);
  for (auto report : reports_) delete (report);
}

void WeatherReport::UpdateData() {
  for (auto report : reports_) {
    weather_api::City result = weather_api_->GetCity(report->city_name);
    report->Populate(result);
  }
}