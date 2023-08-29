#pragma once

#include <initializer_list>
#include <sstream>
#include <string>
#include <variant>

#include "../../components/table/table.h"

#define Parameters std::vector<std::string>

namespace mdb {

using return_type = std::variant<Table, Tables, Columns>;
using function_type =
    std::function<return_type()>;

Table select() {
  // Table table = std::get<Table>(source);
  // Table result;
  // if (params[index + 1] == "*") {
  //   for (auto& key : table.get_keys()) {
  //     result.add(key, table.get(key));
  //   }
  // } else {
  //   for (auto col_name : params) {
  //     result.add(col_name, table.get(col_name));
  //   }
  // }
  // return result;

  return Table();
}

}  // namespace mdb