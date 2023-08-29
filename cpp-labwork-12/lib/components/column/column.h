#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <memory>

namespace mdb {

using data_type = std::variant<int, float, double, bool, std::string>;

template <typename T>
class Column {
 public:
  void add_data(T value) {
    if (primary_) {
      if (std::find(data_.begin(), data_.end(), value) == data_.end()) {
        data_.push_back(value);
      };
    } else {
      data_.push_back(value);
    }
  };

  T at(size_t index) { return data_.at(index); };
  std::vector<T> get_data(size_t index) { return data_; };
  size_t get_size() { return data_.size(); };

  void print(size_t index) const {
    std::visit([](const auto& value) { std::cout << value; }, data_.at(index));
  };

  void set_primary() { primary_ = true; };

 private:
  std::vector<T> data_;
  bool primary_;
  bool foreign_;
};

using Columns =
    std::unordered_map<std::string, std::shared_ptr<Column<data_type>>>;

}  // namespace mdb