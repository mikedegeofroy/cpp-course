#pragma once

#include <filesystem>
#include <istream>

#include <vector>
#include <iostream>


namespace omfl {

// Classes
class Argument {

  protected:
    std::string key_;
    std::string type_;
    bool valid_ = true;

  public:
    std::string key();
    std::string type();
    bool valid();
    void setValid(bool valid);

    Argument& operator[] (int index);

    Argument& Get(std::string location);
    
    int AsInt();
    bool IsInt();
    int AsIntOrDefault(int default_value);

    float AsFloat();
    bool IsFloat();
    float AsFloatOrDefault(float default_value);

    std::string AsString();
    bool IsString();
    std::string AsStringOrDefault(std::string default_value);

    bool AsBool();
    bool IsBool();
    bool AsBoolOrDefault(bool default_value);

    bool IsArray();

};

class Integer : public Argument {
  int value_ = 0;

  public:
    int value();

    Integer(std::string key, std::string value);
};

class Float : public Argument {
  float value_ = 0;

  public:
    float value();

    Float(std::string key, std::string value);
};

class String : public Argument {
  std::string value_ = "";

  public:
    std::string value();

    String(std::string key, std::string value);
};

class Bool : public Argument {
  bool value_;

  public:
    bool value();

    Bool(std::string key, std::string value);
};

class Array : public Argument {
  std::vector<Argument*> values_;

  public:

    std::vector<Argument*> values();

    int size();

    Array(std::string key, std::string value);

};

class Section : public Argument {

  std::vector<Argument*> arguments_;

  Argument& getSubsection(std::vector<std::string> key);

  public:

    void addArgument(Argument* argument);

    Argument& Get(std::string location);

    bool valid();

    // Constructor

    Section(std::string key);

};


// Parse

Section parse(std::string input);

Section parseFile(std::string filePath);


}// namespace
