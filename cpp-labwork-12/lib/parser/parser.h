#pragma once

#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cctype>

enum NodeType {
  Select = 1,
  From = 2,
  Where = 3,
  // Column = 4,
  // Table = 5,
  // Condition = 6,
  // Operator = 7,
  // Value = 8
};

std::unordered_map<std::string, NodeType> keywords = {
    {"select", Select}, {"from", From}, {"where", Where}};

struct FunctionCall {
  NodeType type;
  std::vector<std::string> tokens;
  size_t index;
};

std::stack<FunctionCall> parse(const std::vector<std::string>& tokens) {
  std::stack<FunctionCall> callstack;
  size_t index = 0;
  size_t location = 0;

  while (index < tokens.size() && keywords[tokens[index]]) {
    location = index;
    index++;

    while (index < tokens.size() && !keywords[tokens[index]]) {
      index++;
    }

    callstack.push(FunctionCall { keywords[tokens[location]], tokens, location });
  }


  return callstack;
}