#include <iostream>
#include <string>
#include <vector>

#pragma once

namespace ArgumentParser {

class ArgParser {
  // A class for individual arguments
  class Argument {

    std::vector<std::string> key_;

    // Storage for most values
    std::vector<std::string> string_value_;
    
    // Bool
    bool* bool_storage_pointer_ = nullptr;

    // Strings
    std::string* string_storage_pointer_ = nullptr;

    // Ints
    std::vector<int>* int_storage_pointer_ = nullptr;

    std::string help_ = "";

    bool stored_ = false;
    bool exists_ = false;
    bool default_ = false;
    bool positional_ = false;
    size_t min_args_ = 1;

    size_t value_count_ = 1;

    public:

      Argument(const std::string& key = "", const std::string& key_long = "") : key_  { key, key_long } {}

      void SetValue(const std::string& value) {

        exists_ = true;

        if(default_) {
          default_ = false;
          string_value_.erase(string_value_.begin());
        }

        string_value_.push_back(value);

        if(stored_) {
          if(string_storage_pointer_ != nullptr) {
            *string_storage_pointer_ = value;
          } else if (int_storage_pointer_ != nullptr) {
            (*int_storage_pointer_).push_back(std::stoi(value));
          }
        }
      }

      void Seen() {
        exists_ = true;
        if(bool_storage_pointer_ != nullptr) {
          *bool_storage_pointer_ = true;
        }
      }

      Argument& Default(const char* value) {
        default_ = true;
        exists_ = true;
        string_value_.push_back(value);
        if(stored_)
          *string_storage_pointer_ = value;
        return *this;
      }

      Argument& Default( bool value ) {
        default_ = true;
        exists_ = true;
        string_value_.push_back("");
        if(stored_)
          *bool_storage_pointer_ = value;
        return *this;
      }

      Argument& StoreValue(std::string& value_location) {

        stored_ = true;
        string_storage_pointer_ = &value_location;

        return *this;
      }

      Argument& StoreValue(bool& value_location) {

        stored_ = true;
        bool_storage_pointer_ = &value_location;

        return *this;
      }

      

      Argument& StoreValues(std::vector<int>& value_location) {

        stored_ = true;
        int_storage_pointer_ = &value_location;

        return *this;
      }

      Argument& MultiValue(size_t min_args = 1) {
        min_args_ = min_args;

        return *this;
      }


      Argument& Positional() {
        positional_ = true;

        return *this;
      }

      void SetHelp(std::string help) {
        help_ = help;
      }

      // Getters
      std::vector<std::string> key() { return key_; }
      std::vector<std::string> string() { return string_value_; }
      bool positional() { return positional_; }
      bool exists() { return exists_; }
      size_t min_args() { return min_args_; }

};

  // This holds all the arguments
  std::vector<Argument*> arguments_;

  bool help_ = false;

  // Helper function to find argument in arguments_ list.
  Argument* FindArgument(std::string key) {

    for (int i = 0; i < arguments_.size(); i++) {

      std::vector<std::string> args = arguments_[i]->key();

      if (key == args[0] || key == args[1]) {
        return arguments_[i];
      }
    }

    return nullptr;
  }

  // Cleans argument string from -- or -
  std::string CleanArgument(std::string raw_key){
    if (raw_key[1] == '-') {
      return raw_key.substr(2);
    } else if (raw_key[0] == '-'){
      return raw_key.substr(1);
    }

    return raw_key;
  }

 public:
  ArgParser(std::string name){};

  Argument& AddStringArgument(char key) {

    std::string short_key(1, key);
    Argument* new_argument = new Argument(short_key);
    arguments_.push_back(new_argument);

    return *new_argument;
  }

  Argument& AddStringArgument(std::string long_key) {
    Argument* new_argument = new Argument(long_key);
    arguments_.push_back(new_argument);

    return *new_argument;
  }
  
  Argument& AddStringArgument(char key, std::string long_key, std::string info = "") {

    std::string short_key(1, key);
    Argument* new_argument = new Argument(short_key, long_key);
    new_argument->SetHelp(info);
    arguments_.push_back(new_argument);

    return *new_argument;
  }

  Argument& AddIntArgument(char key) {

    std::string short_key(1, key);
    Argument* new_argument = new Argument(short_key);
    arguments_.push_back(new_argument);

    return *new_argument;
  }

  Argument& AddIntArgument(std::string long_key) {
    Argument* new_argument = new Argument(long_key);
    arguments_.push_back(new_argument);

    return *new_argument;
  }
  
  Argument& AddIntArgument(char key, std::string long_key, std::string info = "") {

    std::string short_key(1, key);
    Argument* new_argument = new Argument(short_key, long_key);
    new_argument->SetHelp(info);
    arguments_.push_back(new_argument);

    return *new_argument;
  }

  Argument& AddIntArgument(std::string long_key, std::string info) {

    Argument* new_argument = new Argument(long_key);
    new_argument->SetHelp(info);
    arguments_.push_back(new_argument);

    return *new_argument;
  }

  Argument& AddFlag(char key) {

    std::string short_key(1, key);
    Argument* new_argument = new Argument(short_key);
    new_argument->MultiValue(0);
    arguments_.push_back(new_argument);

    return *new_argument;
  }

  Argument& AddFlag(std::string long_key, std::string info = "") {
    Argument* new_argument = new Argument(long_key);
    new_argument->MultiValue(0);
    new_argument->SetHelp(info);
    arguments_.push_back(new_argument);

    return *new_argument;
  }
  
  Argument& AddFlag(char key, std::string long_key, std::string info = "") {

    std::string short_key(1, key);
    Argument* new_argument = new Argument(short_key, long_key);
    new_argument->MultiValue(0);
    new_argument->SetHelp(info);
    arguments_.push_back(new_argument);

    return *new_argument;
  }

  // bool Parse(int argc, char **argv);

  Argument& AddHelp(char key, std::string long_key, std::string info) {

    help_ = true;

    std::string short_key(1, key);
    Argument* new_argument = new Argument(short_key, long_key);
    new_argument->MultiValue(0);
    new_argument->SetHelp(info);
    arguments_.push_back(new_argument);

    return *new_argument;
  }

  bool Help() {
    return true;
  }

  void HelpDescription() {
    std::cout << "My Parser\n";
    std::cout << "Some Description about program\n";
    std::cout << "\n";
    std::cout << "-i,  --input=<string>,  File path for input file [repeated, min args = 1]\n";
    std::cout << "-s,  --flag1,  Use some logic [default = true]\n";
    std::cout << "-p,  --flag2,  Use some logic\n";
    std::cout << "     --number=<int>,  Some Number\n";
    std::cout << "\n";
    std::cout << "-h, --help Display this help and exit\n";
  }

  std::string GetStringValue(std::string key) {

    Argument* pointer = FindArgument(key);
    if(pointer != nullptr)
      return pointer->string()[0];
    return "";
  }

  int GetIntValue(std::string key, int index = 0) {
    Argument* pointer = FindArgument(key);
    if(pointer != nullptr)
      return std::stoi(FindArgument(key)->string()[index]);
    return 0;
  }

  bool GetFlag(std::string key) {
    Argument* pointer = FindArgument(key);
    if(pointer != nullptr)
      return FindArgument(key)->exists();
    return false;
  }

  bool Parse(int argc, char** argv) {
    std::vector<std::string> arguments(argv, argv + argc);
    return Parse(arguments);
  }

  bool Parse(std::vector<std::string> arguments) {

    Argument* positional = nullptr;

    for(int i = 0; i < arguments_.size(); i++){
      if(arguments_[i]->positional())
        positional = arguments_[i];
    }

    for (int i = 0; i < arguments.size(); i++) {

      char* string = strdup(arguments[i].c_str());

      char* token = strtok(string, "=");
      if (token != NULL) arguments.erase(arguments.begin() + i);
      int j = 0;

      while (token != NULL) {
        arguments.insert(arguments.begin() + i + j, token);
        j++;
        token = strtok(NULL, "=");
      }

      for(int k = 1; k < arguments[i].length() && (arguments[i][0] == '-' && arguments[i][1] != '-'); k++){

        std::string short_key(1, arguments[i][k]);
        Argument* argument = FindArgument(short_key);

        if (argument != nullptr) {
          argument->Seen();
          int m = 0;
          while (i + m + 1 < arguments.size() && arguments[i + m + 1][0] != '-') {
            m++;
            argument->SetValue(arguments[i + k]);
          }
        }

      }

      if (arguments[i][0] == '-' && arguments[i][1] == '-') {
        
        Argument* argument = FindArgument(CleanArgument(arguments[i]));

        if (argument != nullptr) {
          argument->Seen();
          while (i + 1 < arguments.size() && arguments[i + 1][0] != '-') {
            i++;
            argument->SetValue(arguments[i]);
          }
        }
      }

    }
    

    if(positional != nullptr){
      for(int k = 1; k < arguments.size(); k++){
        if(arguments[k][0] != '-') {
          positional->SetValue(arguments[k]);
        }
      }
    }

    for (int i = 0; i < arguments_.size(); i++) {
      std::vector<std::string> data = arguments_[i]->string();
      if((data.size() < arguments_[i]->min_args() || !arguments_[i]->exists()) && !help_ ) {
        return false;
      }
    }

    return true;
  };
};

}  // namespace ArgumentParser