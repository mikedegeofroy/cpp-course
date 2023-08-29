#include "gui.h"

namespace gui {
UserInterface::UserInterface(std::string api_key, 
                        const std::vector<std::string>& cities){
  data_source = new WeatherReport(api_key);
  for (auto& city : data_source->Get(cities)) {
    radiobox_list.push_back(city->city_name);
  };
}

UserInterface::~UserInterface() { delete (data_source); }

void UserInterface::Run() {
  auto component = Build();
  screen.Loop(component);
}

Element UserInterface::DayView() { 
  auto data = data_source->GetReports()[city_index_];

  std::string temperature = DecimalSetter(data->daily_report[day_index_].temperature[0], 2);
      
  std::string apparent_temperature = DecimalSetter(data->daily_report[day_index_].apparent_temperature[0], 2);

  std::string precipitation_probability = 
        DecimalSetter(data->daily_report[day_index_].precipitation_probability[day_index_], 0);

  Graph temperature_graph(data->daily_report[day_index_].temperature);

  auto root = hbox({
    separator() | borderStyled(EMPTY),
    text("") | ftxui::size(HEIGHT, EQUAL, 2) | borderStyled(EMPTY),
    vbox({
      vbox({
        hbox({
          WeatherIcon(1) | center,
          vbox({
            WeatherDescription(1) | center,
          }) | flex | borderStyled(EMPTY)
        }) | flex | borderStyled(EMPTY),
        separator(),
        hbox({
          vbox({
            text(data->city_name),
            text(""),
            text(std::to_string(data->longitude) + "°N"),
            text(std::to_string(data->latitude) + "°E")
          }) | flex | borderStyled(EMPTY),
          text("") | ftxui::size(WIDTH, EQUAL, 2),
          vbox({
            text(DateParser(data->daily_report[day_index_].time[0])),
            text(""),
            text("Temperature: " + temperature + " C°"),
            text("Feels like: " + apparent_temperature + "C°"),
            text("Precipitation probability: " + precipitation_probability + "%"),
          }) | flex | borderStyled(EMPTY)
        }),
      }),
      hbox({
        window(text("temperature graph"), graph(std::ref(temperature_graph)) | flex ) | flex
      }) | flex 
    }),
    hbox({
      text("") | ftxui::size(WIDTH, EQUAL, 2),
      vbox({
        Map(data->map) | border
      }) | flex,
      text("") | ftxui::size(WIDTH, EQUAL, 2)
    }) | flex
  });

  return root;
}

Component UserInterface::BackButton(UserInterface* parent) {
  class Impl : public ftxui::ComponentBase {
  public:
    Impl(UserInterface* parent) : parent_(parent), view_index_(parent_->view_index_) {}

    Element Render() override {
      if (view_index_ == 1) {
        return text("Back") | reflect(box_);
      }
      return text("");
    }

    bool OnEvent(Event event) override {
      if (event.is_mouse()) {
        if (event.mouse().button == Mouse::Left &&
            event.mouse().motion == Mouse::Released) {
          
          if (box_.Contain(event.mouse().x, event.mouse().y)) {
            if (view_index_ == 1) {
              view_index_ = 0;
            }
            return true;
          }
        }
      }

      return false;
    }

    Component component_;
    UserInterface* parent_;
    std::vector<WeeklyReport*> reports_;
    int& view_index_;
    Box box_;
  };

  return ftxui::Make<Impl>(parent);
}

Component UserInterface::WeekView(UserInterface* parent) {
  class Impl : public ftxui::ComponentBase {
  public:
    Impl(UserInterface* parent) : parent_(parent), city_index_(parent_->city_index_) {
      reports_ = parent_->data_source->GetReports();
      boxes_.resize(reports_[city_index_]->daily_report.size());
    }

    Element Render() override { 
      auto data = reports_[city_index_]->daily_report;

      std::string temperature = DecimalSetter(data[0].temperature[0], 2);

      std::string apparent_temperature = DecimalSetter(data[0].apparent_temperature[0], 2);

      std::string precipitation_probability = DecimalSetter(data[0].precipitation_probability[0], 0);

      Elements elements;
      
      for (int i = 0; i < data.size() && i < parent_->forecast_days_; ++i) {

        auto element = vbox({
          vbox({
            WeatherIcon(data[i].weathercode),
            text(""),
            text(temperature + " C°"),
            text("Feels: " + apparent_temperature + "C°"),
            text("Rain %: " + precipitation_probability),
          }) | yflex | border,
          text(DateParser(data[i].time[0])) | center,
        }) | center;

        elements.push_back(element | reflect(boxes_[i]));
      }

      return hbox({
        separator() | borderStyled(EMPTY),
          hbox({
            std::move(elements)
          }) | yflex | center
      }) | flex | reflect(box_); 
    }

    bool OnEvent(Event event) override {
      if (event.is_mouse()) {
        for (int i = 0; i < boxes_.size(); ++i) {
          if (!boxes_[i].Contain(event.mouse().x, event.mouse().y)) {
            continue;
          }

          if (event.mouse().button == Mouse::Left &&
              event.mouse().motion == Mouse::Released) {
            parent_->day_index_ = i;
            parent_->view_index_ = 1;
            return true;
          }
        }
      }

      return false;
    }

    Component component_;
    UserInterface* parent_;
    std::vector<WeeklyReport*> reports_;
    int& city_index_;
    Box box_;
    std::vector<Box> boxes_;
  };

  return ftxui::Make<Impl>(parent);
}

Component UserInterface::Build() {
  auto view_container = Container::Tab({}, &view_index_);

  auto week_view = Container::Horizontal({
    WeekView(this)
  });
  auto day_view = ftxui::Renderer([this] { return this->DayView(); });
  
  view_container->Add(week_view);
  view_container->Add(day_view);

  auto root = Container::Horizontal({
    Container::Vertical({
      BackButton(this) | align_right,
      Radiobox(&radiobox_list, &city_index_) | center | flex,
      BackButton(this) | align_right
    }) | borderStyled(EMPTY),
    view_container | flex,
  }) | border;

  return ftxui::CatchEvent(root, [this](ftxui::Event event) { 
    if (event == ftxui::Event::Character('+') || event == ftxui::Event::Character('=')) {
      forecast_days_ = ++forecast_days_ % 8;
      return true;
    } else if (event == ftxui::Event::Character('-')) {
      forecast_days_ = (--forecast_days_ < 0 ? forecast_days_ = 0 : forecast_days_) % 7;
      return true;
    } else  if (event == ftxui::Event::Character('n')) {
      city_index_ = ++city_index_ % radiobox_list.size();
      return true;
    } else  if (event == ftxui::Event::Character('m')) {
      city_index_ = (--city_index_ < 0 ? city_index_ = city_index_ * (-1) 
                                      : city_index_) % radiobox_list.size();
      return true;
    } else if (event == ftxui::Event::Escape) {
      if (view_index_ == 1) {
        view_index_ = 0;
      } else {
        screen.Exit();
      }
      return true;
    } else if (event == ftxui::Event::Character('q')) {
      screen.Exit();
      return true;
    }
    return false; 
  });
}

}

