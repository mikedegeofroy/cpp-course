#include "ftxui/component/captured_mouse.hpp"  // for CapturedMouse
#include "ftxui/component/component.hpp"       // for Make, Button
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/event.hpp"           // for Event, Event::Return
#include "ftxui/component/mouse.hpp"  // for Mouse, Mouse::Left, Mouse::Pressed
#include "ftxui/component/screen_interactive.hpp"  // for Component
#include "ftxui/dom/elements.hpp"  // for operator|, Decorator, Element, operator|=, bgcolor, color, reflect, text, bold, border, inverted, nothing
#include "ftxui/screen/box.hpp"    // for Box
#include "ftxui/screen/color.hpp"  // for Color
#include "ftxui/util/ref.hpp"      // for Ref, ConstStringRef

#include <ctime>
#include <sstream>
#include <iomanip>

namespace gui {

using namespace ftxui;

std::string DateParser(const tm& time_object, const std::string& pattern = "%a %d %b") {
  char buf[80];
  strftime(buf, sizeof(buf), "%a %e %b", &time_object);
  return buf;
}

std::string DecimalSetter(float value, int decimals) {
  std::stringstream data;
  data << std::fixed << std::setprecision(decimals) << value;
  return data.str();
}

Element WeatherIcon(int weather_code) {
  Element icon;
  if (weather_code == 0) {
    icon = hbox(vbox({
        ftxui::text("   \\   /  "),
        ftxui::text("    .-.    "),
        ftxui::text("-- (   ) --"),
        ftxui::text("    `-`    "),
        ftxui::text("   /    \\  ")
    }));
  } else if (1 <= weather_code && weather_code <= 3) {
    icon = hbox(ftxui::vbox({
        ftxui::text("   \\   /        "),
        ftxui::text("    .-. __      "),
        ftxui::text("-- (._(    ).-. "),
        ftxui::text("  (___._______.)"),
        ftxui::text("") | ftxui::size(HEIGHT, EQUAL, 1)
    }));

  } else if (45 <= weather_code && weather_code <= 48) {
    icon = ftxui::hbox(ftxui::vbox({
        ftxui::text(" -_-_-_-_-  "),
        ftxui::text(" -_-_-_-_-  "),
        ftxui::text(" -_-_-_-_-  "),
        ftxui::text("") | ftxui::size(HEIGHT, EQUAL, 2)
    }));

  } else if (51 <= weather_code && weather_code <= 55) {
    icon = ftxui::hbox(ftxui::vbox({
        ftxui::text("    .--.     "),
        ftxui::text(" .-(    ).-. "),
        ftxui::text("(___._____..)"),
        ftxui::text("") | ftxui::size(HEIGHT, EQUAL, 2)
    }));
  } else if (56 <= weather_code && weather_code <= 57) {
    icon = ftxui::hbox(ftxui::vbox({
        ftxui::text("    .--.     "),
        ftxui::text(" .-(    ).-. "),
        ftxui::text("(___._____..)"),
        ftxui::text(" '' ' '  ' ' "),
        ftxui::text("") | ftxui::size(HEIGHT, EQUAL, 1)
    }));
  } else if (61 <= weather_code && weather_code <= 65) {
    icon = ftxui::hbox(ftxui::vbox({
        ftxui::text("    .--.     "),
        ftxui::text(" .-(    ).-. "),
        ftxui::text("(___._____..)"),
        ftxui::text(" | |  '|  '| "),
        ftxui::text("") | ftxui::size(HEIGHT, EQUAL, 1)
    }));
  } else if (66 <= weather_code && weather_code <= 67) {
    icon = ftxui::hbox(ftxui::vbox({
        ftxui::text("    .--.     "),
        ftxui::text(" .-(    ).-. "),
        ftxui::text("(___._____..)"),
        ftxui::text(" '| *  '| *  "),
        ftxui::text("") | ftxui::size(HEIGHT, EQUAL, 1)
    }));
  } else if (71 <= weather_code && weather_code <= 75) {
    icon = ftxui::hbox(ftxui::vbox({
        ftxui::text("    .--.     "),
        ftxui::text(" .-(    ).-. "),
        ftxui::text("(___._____..)"),
        ftxui::text("  *  **  * * "),
        ftxui::text("") | ftxui::size(HEIGHT, EQUAL, 1)
    }));
  } else if (weather_code == 77) {
    icon = ftxui::hbox(ftxui::vbox({
        ftxui::text("    .--.     "),
        ftxui::text(" .-(    ).-. "),
        ftxui::text("(___._____..)"),
        ftxui::text(" '* ' '  * ' "),
        ftxui::text("") | ftxui::size(HEIGHT, EQUAL, 1)
    }));
  } else if (80 <= weather_code && weather_code <= 82) {
    icon = ftxui::hbox(ftxui::vbox({
        ftxui::text("    .--.     "),
        ftxui::text(" .-(    ).-. "),
        ftxui::text("(___._____..)"),
        ftxui::text(" | | || || | "),
        ftxui::text("") | ftxui::size(HEIGHT, EQUAL, 1)
    }));
  } else if (85 <= weather_code && weather_code <= 86) {
    icon = ftxui::hbox(ftxui::vbox({
        ftxui::text("    .--.     "),
        ftxui::text(" .-(    ).-. "),
        ftxui::text("(___._____..)"),
        ftxui::text(" * ** * * *  "),
        ftxui::text("") | ftxui::size(HEIGHT, EQUAL, 1)
    }));

  } else if (95 <= weather_code && weather_code <= 99) {
    icon = ftxui::hbox(ftxui::vbox({
        ftxui::text("    .--.     "),
        ftxui::text(" .-(    ).-. "),
        ftxui::text("(___._____..)"),
        ftxui::text(" |'| /  |' | "),
        ftxui::text("") | ftxui::size(HEIGHT, EQUAL, 1),
    }));

  } else {
    icon = ftxui::hbox(ftxui::vbox({
        ftxui::text("    .--.     "),
        ftxui::text(" .-(    ).-. "),
        ftxui::text("(___._____..)"),
        ftxui::text("\n") | ftxui::size(HEIGHT, EQUAL, 2)
    }));
  }

  return icon;
}

Element WeatherDescription(int weather_code) {
  Element weather_description;
  if (weather_code == 0) {
      weather_description = vbox({text("Clear sky")});
  } else if (1 <= weather_code && weather_code <= 3) {
    weather_description = vbox({text("Mainly clear, partly cloudy,"), text("and overcast") | center});
  } else if (45 <= weather_code && weather_code <= 48) {
    weather_description = vbox({text("Fog and depositing rime fog")});
  } else if (51 <= weather_code && weather_code <= 55) {
    weather_description = vbox({text("Drizzle: Light, moderate,"), text("and dense intensity") | center});
  } else if (56 <= weather_code && weather_code <= 57) {
    weather_description = vbox({text("Freezing Drizzle:"), text("Light and dense intensity") | center});
  } else if (61 <= weather_code && weather_code <= 65) {
    weather_description = vbox({text("Rain: Slight, moderate"), text("and heavy intensity") | center});
  } else if (66 <= weather_code && weather_code <= 67) {
    weather_description = vbox({text("Freezing Rain:"), text("Light and heavy intensity") | center});
  } else if (71 <= weather_code && weather_code <= 75) {
    weather_description = vbox({text("Snow fall: Slight, moderate,"), text(" and heavy intensity") | center});
  } else if (weather_code == 77) {
    weather_description = vbox({text("Snow grains")});
  } else if (80 <= weather_code && weather_code <= 82) {
    weather_description = vbox({text("Rain showers: Slight,"), text("moderate, and violent") | center});
  } else if (85 <= weather_code && weather_code <= 86) {
    weather_description = vbox({text("Snow showers slight"), text("and heavy") | center});
  } else if (95 <= weather_code && weather_code <= 99) {
    weather_description = vbox({text("Thunderstorm with"), text("slight and heavy hail") | center});
  } else {
    weather_description = vbox({text("Cloudy")});
  }
  return weather_description;
}

class Graph {
private:
  std::vector<float> resample(std::vector<float>& src, std::size_t newSize) {
    std::vector<float> dst(newSize);
    float scale = float(src.size()) / float(newSize);

    for (std::size_t i = 0; i < newSize; ++i) {
        float srcIndex = float(i) * scale;
        std::size_t srcIndex0 = std::size_t(srcIndex);
        std::size_t srcIndex1 = std::min(srcIndex0 + 1, src.size() - 1);

        // If newSize is smaller than src.size(), 
        // this averages all src values corresponding to this dst index
        if (newSize < src.size()) {
            float total = 0.0;
            for (std::size_t j = srcIndex0; j <= srcIndex1; ++j) {
                total += src[j];
            }
            dst[i] = total / (srcIndex1 - srcIndex0 + 1);
        } else {
            // If newSize >= src.size(), this linearly interpolates as before
            float t = srcIndex - float(srcIndex0);
            dst[i] = (1.0f - t) * src[srcIndex0] + t * src[srcIndex1];
        }
    }

    return dst;
  }

public:
  float min_temp = 0;
  float max_temp = 0;
  int shift = 1;
  std::vector<float> temperature;

  Graph(std::vector<float> temperature_) {
    temperature = temperature_;
    min_temp = *std::min(temperature.begin(), temperature.end());
    max_temp = *std::max(temperature.begin(), temperature.end());
  }

  std::vector<int> operator()(int width, int height) const {
    std::vector<int> output(width);
    for (int i = 0; i < width; ++i) {
      float v = 0;
      v += 0.1f * sin(0.05 * i);
      v *= height;
      v += 0.4f * height;
      output[i] = static_cast<int>(v);
    }
    return output;
  }
};

Element Map(std::vector<std::vector<std::string>> city_map) {
  class Impl : public Node {
    public:
      explicit Impl(std::vector<std::vector<std::string>> city_map) : city_map_(std::move(city_map)) {}

      void ComputeRequirement() override {
        requirement_.flex_grow_x = 1;
        requirement_.flex_grow_y = 1;
        requirement_.flex_shrink_x = 1;
        requirement_.flex_shrink_y = 1;
      }

      void Render(Screen& screen) override {
        int start_x = box_.x_min;
        int start_y = box_.y_min;

        int end_x = box_.x_max + 1;
        int end_y = box_.y_max + 1;

        int map_height = city_map_.size();
        int map_width = city_map_[0].size();
        
        int viewport_height = end_y - start_y;
        int viewport_width = end_x - start_x;


        int x_coord_map = (map_width - viewport_width) / 2;
        int y_coord_map = (map_height - viewport_height) / 2;
        for (int y = start_y; y < end_y && y_coord_map < map_height; ++y) {
          x_coord_map = 0;
          for (int x = start_x; x < end_x && x_coord_map < map_width; ++x) {
            screen.PixelAt(x, y).character = city_map_[y_coord_map][x_coord_map];
            x_coord_map++;
          }
          y_coord_map++;
        }

      }

    private:
      std::vector<std::vector<std::string>> city_map_;
  };

  return std::make_shared<Impl>(city_map);
}

}  // namespace gui