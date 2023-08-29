#pragma once

#include <functional>
#include <memory>
#include <algorithm>
#include <vector>

#include "ftxui/component/captured_mouse.hpp"  // for CapturedMouse
#include "ftxui/component/component.hpp"       // for Make, Button
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/event.hpp"           // for Event, Event::Return
#include "ftxui/component/mouse.hpp"  // for Mouse, Mouse::Left, Mouse::Pressed
#include "ftxui/component/screen_interactive.hpp"  // for Component
#include "ftxui/dom/elements.hpp"  // for operator|, Decorator, Element, operator|=, bgcolor, color, reflect, text, bold, border, inverted, nothing
#include "ftxui/screen/box.hpp"    // for Box

#include "weather_report.h"
#include "components/components.h"

namespace gui {

using namespace ftxui;

#include "ftxui/component/component.hpp"
#include "ftxui/dom/canvas.hpp"

class UserInterface {
 private:
  int view_index_ = 0;
  int city_index_ = 0;
  int day_index_ = 0;
  int forecast_days_ = 4;

  ScreenInteractive screen = ScreenInteractive::Fullscreen();;
  std::vector<std::string> radiobox_list;
  WeatherReport* data_source;

 public:
  UserInterface(std::string api_key, const std::vector<std::string>& cities);

  Element DayView();

  Component WeekView(UserInterface* parent);

  Component BackButton(UserInterface* parent);

  Component Build();

  void Run();

  ~UserInterface();
};

} // namespace gui