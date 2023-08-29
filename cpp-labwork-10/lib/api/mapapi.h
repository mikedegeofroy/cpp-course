#pragma once
#include <cpr/cpr.h>

#include <string>
#include <vector>
// here we have  a function that will take in all the needed data and preform
// the request.

std::vector<std::vector<std::string>> GetMap(float latitude, float longitude) {
  cpr::Response r = cpr::Get(
      cpr::Url{"http://localhost:3000/ascii-map/"},
      cpr::Header{
                  {"lat", std::to_string(latitude)},
                  {"lon", std::to_string(longitude)}
                 });

  std::vector<std::vector<std::string>> result;
  std::vector<std::string> temp;

  std::string& input = r.text;

  for (size_t i = 0; i < input.size(); ++i) {
      if (input[i] != '\n') {
          temp.push_back(std::string(1, input[i]));
      }
      if (input[i] == '\n' || i == input.size() - 1) {
          result.push_back(temp);
          temp.clear();
      }
  }

  return result;
}