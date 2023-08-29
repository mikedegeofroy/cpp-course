#pragma once

#include <cctype>
#include <functional>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <variant>

// what does a database need?

// tokenizer
// parser
// code generator

#include "tokenizer/tokenizer.h"
#include "parser/parser.h"
#include "components/table/table.h"
#include "functions/code_generator.h"

namespace mdb {


class Database {
 private:
  Tables tables_;
  std::stack<FunctionCall> callstack_;

 public:
  Table query(const std::string& query) {

    std::vector<std::string> tokens = tokenize(query);

    callstack_ = parse(tokens);

    return run(callstack_, tables_);
  }

  Table& get(const std::string& name);

  Table& create(const std::string& name) {
    tables_[name] = std::make_shared<Table>(name);
    return *tables_[name];
  }
};

}  // namespace mdb
