#pragma once

#include <stack>
#include <unordered_map>

#include "../components/table/table.h"
#include "../parser/parser.h"
#include "query_language/query_language.h"

// we can probably map a Node Type to a function call, but what does the
// function need to run?

// it would be cool to give it a) the whole string, b) index c) the output of
// the previous function

// we need a datasource and the callstack
namespace mdb {

std::unordered_map<NodeType, function_type> query_language = {
  {Select, select}
};

std::unordered_map<NodeType, function_type> definition_language;
std::unordered_map<NodeType, function_type> manipulation_language;

Table run(std::stack<FunctionCall>& callstack, Tables data_source) {
  FunctionCall head;

  NodeType type;

  // query_language should have a function for each of those things, we can
  // probably keep the result and pass it on.

  return_type result = data_source;

  while (!callstack.empty()) {
    head = callstack.top();
    type = head.type;

    if (query_language[type]) {

        auto function = query_language[type];
        auto params = callstack.top().tokens;
        auto index = callstack.top().index;
        // result = function(params, index, result, &data_source);

    } else if (definition_language[type]) {
      // handle definition language execution
    } else if (manipulation_language[type]) {
      // handle manipulation language execution
    }

    callstack.pop();
  }

  return std::get<Table>(result);
}

}  // namespace mdb
