#include "parser.h"

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>

// Helper functions (Definition)

std::smatch regex(std::string input, std::string exp) {
  std::smatch matches;

  std::regex reg(exp);

  std::regex_search(input, matches, reg);

  return matches;
}

std::string getValueType(std::string value) {
  // Bad code

  if(value.empty()) {
    return "section";
  } else if (!regex(value, "[^\\[]*(\\[.*\\])[^\\]]*").empty()) {
    return "array";
  } else if (!regex(value, "^((?:'|\")[^\"]*(?:'|\"))$").empty()) {
    return "string";
  } else if (!regex(value, "^([+-]?([0-9]+[.][0-9]+))$").empty()) {
    return "float";
  } else if (!regex(value, "^(?:tru|fals)e$").empty()) {
    return "bool";
  } else if (!regex(value, "^([+-]?\\d+)$").empty()) {
    return "integer";
  }
  return "unknown";

}

std::vector<std::string> splitString(std::string str, std::string split_by = "\n") {
  std::vector<std::string> tokens;
  std::string token;

  std::regex r("\\s+");
  std::regex r2("#.*");
  std::regex rgx(split_by);
  std::sregex_token_iterator iter(str.begin(), str.end(), rgx, -1);
  std::sregex_token_iterator end;
  for ( ; iter != end; ++iter) {   
    token = *iter;
    token = std::regex_replace(token, r, "");
    token = std::regex_replace(token, r2, "");
    if(token[0] == '#')
      break;
    if(token.length() > 0)
      tokens.push_back(token);
  }

  return tokens;
}

std::string omfl::Argument::key() { return key_; }
std::string omfl::Argument::type() { return type_; }
bool omfl::Argument::valid() { return valid_; }

omfl::Argument& omfl::Argument::Get(std::string location) {
  return (static_cast <Section*> (this))->Get(location);
};

// Integer Argument Functions

bool omfl::Argument::IsInt() { return type_ == "int"; }
int omfl::Argument::AsInt() {
  return (static_cast <Integer*> (this))->value();
}
int omfl::Argument::AsIntOrDefault(int default_value) {
  if(type_ == "int")
    return (static_cast <Integer*> (this))->value();
  return default_value;
}

// Float Argument Functions

bool omfl::Argument::IsFloat() { return type_ == "float"; }
float omfl::Argument::AsFloat() {
  return (static_cast <Float*> (this))->value();
}
float omfl::Argument::AsFloatOrDefault(float default_value) {
  if(type_ == "float")
    return (static_cast <Float*> (this))->value();
  return default_value;
}

// String Argument Functions

bool omfl::Argument::IsString() { return type_ == "string"; }
std::string omfl::Argument::AsString() {
  return (static_cast <String*> (this))->value();
}
std::string omfl::Argument::AsStringOrDefault(std::string default_value) {
  if(type_ == "string")
    return (static_cast <String*> (this))->value();
  return default_value;
}

// Bool Argument Functions

bool omfl::Argument::IsBool() { return type_ == "bool"; }
bool omfl::Argument::AsBool() {
  return (static_cast <Bool*> (this))->value();
};
bool omfl::Argument::AsBoolOrDefault(bool default_value) {
  if(type_ == "bool")
    return (static_cast <Bool*> (this))->value();
  return default_value;
};

// Array Argument Functions

bool omfl::Argument::IsArray() { return type_ == "array"; }

// Derived Integer Functions

omfl::Integer::Integer(std::string key, std::string value) {
  type_ = "int";
  key_ = key;
  value_ = std::stoi(value);
}
int omfl::Integer::value() { return value_; }

// Derived Float Functions

omfl::Float::Float(std::string key, std::string value) {
  type_ = "float";
  key_ = key;
  value_ = std::stof(value);
}
float omfl::Float::value() { return value_; }

// Derived String Functions

omfl::String::String(std::string key, std::string value) {
  type_ = "string";
  key_ = key;
  value_ = value;
}
std::string omfl::String::value() { return value_; }

// Derived Bool Functions

omfl::Bool::Bool(std::string key, std::string value) {
  type_ = "bool";
  key_ = key;
  if (value == "true") {
    value_ = true;
  } else {
    value_ = false;
  }
}
bool omfl::Bool::value() { return value_; }

// Derived Array Functions

omfl::Array::Array(std::string key, std::string value) {
  type_ = "array";
  key_ = key;
  // Some code that sets values
  std::vector<std::string> values;
  std::string temp = "";
  std::stack<char> bracketStack;
  for (std::string::size_type i = 0; i < value.length(); i++) {
    char c = value[i];
    if (c == '[') {
      bracketStack.push(c);
      temp += c;
    } else if (c == ']') {
      if (bracketStack.empty() || bracketStack.top() != '[') {
        setValid(false);
        temp = "";
        while (!bracketStack.empty()) {
            bracketStack.pop();
        }
      } else {
        bracketStack.pop();
        temp += c;
        if (bracketStack.empty()) {
          values.push_back(temp);
          temp = "";
        }
      }
    } else if (!bracketStack.empty()) {
        temp += c;
    } else if (c != ',') {
      temp += c;
      if (i + 1 != value.length() && value[i + 1] == ',') {
        values.push_back(temp);
        temp = "";
      } else if (i + 1 == value.length()) {
        values.push_back(temp);
      }
    }
  }

  if (!bracketStack.empty()) {
    setValid(false);
  }

  for (int i = 0; i < values.size(); i++) {

    std::string type = getValueType(values[i]);

    // Fix shit code here
    if (type == "array") {
      Array* argument = new Array("", values[i].substr(1, values[i].length() - 2) );
      values_.push_back(argument);
    } else if (type == "string") {
      String* argument = new String("", values[i].substr(1, values[i].length() - 2) );
      values_.push_back(argument);
    } else if (type == "float") {
      Float* argument = new Float("", values[i]);
      values_.push_back(argument);
    } else if (type == "bool") {
      Bool* argument = new Bool("", values[i]);
      values_.push_back(argument);
    } else if (type == "integer") {
      Integer* argument = new Integer("", values[i]);
      values_.push_back(argument);
    } else {
      setValid(false);
    }
    
  }

}
std::vector<omfl::Argument*> omfl::Array::values() {
  return values_;
}
int omfl::Array::size() {
  return values_.size();
}

// Derived Section Functions

omfl::Section::Section(std::string key) {
  type_ = "section";
  key_ = key;
}
omfl::Argument& omfl::Section::getSubsection(std::vector<std::string> key) {

  for (int i = 0; i < arguments_.size(); i++) {
    if (arguments_[i]->key() == key[0]) {
      
      if(key.size() == 1) {
        if (arguments_[i]->type() == "section") {
          return  *(static_cast <Section*> (arguments_[i]));
        }
        return *arguments_[i];
      } else {
        key.erase(key.begin());
        return  (static_cast <Section*> (arguments_[i]))->getSubsection(key);
      }

    }
  }


  Section* argument = new Section(key[0]);
  arguments_.push_back(argument);

  if(key.size() == 1)
    return *(static_cast <Section*> (argument));
  key.erase(key.begin());
  return argument->getSubsection(key);
}

void omfl::Section::addArgument(omfl::Argument* argument) {

  for (int i = 0; i < arguments_.size(); i++) {
    if (arguments_[i]->key() == argument->key()) {
      valid_ = false;
      break;
    }
  }

  arguments_.push_back(argument);
}
omfl::Argument& omfl::Section::Get(std::string location) {

  std::vector<std::string> key = splitString(location, "\\.");

  return getSubsection(key);

}
bool omfl::Section::valid() {

  for (int i = 0; i < arguments_.size() && valid_; i++ ) {
    valid_ = arguments_[i]->valid();
  }

  return valid_;
}
void omfl::Argument::setValid(bool valid) { valid_ = valid; }
omfl::Argument& omfl::Argument::operator[] (int index) {
  if ( index < (*(static_cast <Array*> (this))).size() )
    return *(static_cast <Array*> (this))->values()[index];
  Argument* argument = new Argument;
  return *argument;
}

// Parser

omfl::Section omfl::parseFile(std::string filePath) {

  std::ifstream t(filePath);
  std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

  return parse(str);

}

omfl::Section omfl::parse(std::string input) {
  Section root("root");

  Section* currentSection = &root;

  std::vector<std::string> input_vector = splitString(input);

  for (int i = 0; i < input_vector.size(); i++) {

    std::string key = regex(input_vector[i], "^[^=]+").str();
    std::string value = regex(input_vector[i], "=([^\\s]*)").str(1);

    // (!A ^ B) v (A ^ !B)
    //  0 0 | 0 0 | 0
    //  0 1 | 1 0 | 1
    //  1 0 | 0 1 | 1
    //  1 1 | 0 0 | 0

    if ( (!regex(key, "[!.*\"]").empty() || ( key.empty() || value.empty() ) ) && regex(key, "\\[[a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+)*(?!\\.)\\]").empty() ) {
      currentSection->setValid(false);
      break;
    }

    if (!key.empty() || !regex(key, "\\[[a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+)*(?!\\.)\\]").empty()) {
      // Set Value and type

      std::string type = getValueType(value);
      
      if (type == "section") {
        // value.substr(1, value.length() - 2);
        currentSection = (static_cast <Section*> (&root.Get(key.substr(1, key.length() - 2))));
      } else if (type == "array") {
        Array* argument = new Array(key, value.substr(1, value.length() - 2) );
        currentSection->addArgument(argument);
      } else if (type == "string") {
        String* argument = new String(key, value.substr(1, value.length() - 2) );
        currentSection->addArgument(argument);
      } else if (type == "float") {
        Float* argument = new Float(key, value);
        currentSection->addArgument(argument);
      } else if (type == "bool") {
        Bool* argument = new Bool(key, value);
        currentSection->addArgument(argument);
      } else if (type == "integer") {
        Integer* argument = new Integer(key, value);
        currentSection->addArgument(argument);
      } else {
        currentSection->setValid(false);
      }
    }


  }

  return root;
}