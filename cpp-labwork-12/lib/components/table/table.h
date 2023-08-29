#pragma once

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>

#include "../column/column.h"

namespace mdb {

using Values = std::vector<std::pair<std::string, data_type>>;
using Keys = std::set<std::string>;

class Table {
 public:
  Table() {}
  Table(const std::string& table_name) : table_name_(table_name) {}
  Table(Columns columns) : columns_(columns) {}
  Table(Table& other) : table_name_(other.table_name_), primary_key_(other.primary_key_), foreign_key_(other.foreign_key_), keys_(other.keys_) {}

  Table& add(const std::string& key) {
    keys_.insert(key);
    columns_[key] = std::make_shared<Column<data_type>>();
    return *this;
  };

  Table& add(const std::string& name, Column<data_type> column) {
    keys_.insert(name);
    columns_[name] = std::make_shared<Column<data_type>>(column);
    return *this;
  };

  Table& add_records(Values records) {
    for (auto& record : records) {
      (*columns_[record.first]).add_data(record.second);
    }
    return *this;
  };

  bool find(const std::string& key) {
    return columns_.find(key) != columns_.end();
  };

  Column<data_type>& get(const std::string& key) { return *columns_[key]; };

  Keys get_keys() { return keys_; };

  void Display() {
    size_t max_lines = 0;
    std::cout << "\e[1m";
    for (auto& key : keys_) {
      std::cout << key << "\t\t";
      max_lines = std::max((*columns_[key]).get_size(), max_lines);
    }
    std::cout << "\e[0m\n";
    for (int i = 0; i < max_lines; ++i) {
      for (auto& key : keys_) {
        if (i < (*columns_[key]).get_size()) {
          (*columns_[key]).print(i);
          std::cout << "\t\t";
        } else {
          std::cout << "NULL\t\t";
        }
      }
      std::cout << "\n";
    }
  };

 private:
  std::string table_name_;
  std::string primary_key_;
  std::string foreign_key_;
  std::set<std::string> keys_;
  Columns columns_;
};

using Tables = std::unordered_map<std::string, std::shared_ptr<Table>>;

}  // namespace mdb