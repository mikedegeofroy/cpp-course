#include "lib/algorithms.h"

#include <gtest/gtest.h>

#include <cmath>
#include <list>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>
#include <functional>

class AlgorithmsTest : public ::testing::Test {
 protected:
  const size_t kCapacity = 10;
  using String = std::string;
  using Vector = std::vector<int>;
  Vector vec;
  String str;

  AlgorithmsTest() : vec(kCapacity) {}
};

TEST_F(AlgorithmsTest, AllOf_1) {
  std::vector<int> vec = {1, 1, 1, 1};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i == 1; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_2) {
  std::vector<int> vec = {1, 1, 1, 1, 2};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i == 1; }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_3) {
  std::vector<int> vec;
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i == 1; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_4) {
  std::vector<int> vec = {2, 2, 2, 2};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i == 1; }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_5) {
  std::vector<int> vec = {-1, -1, -1, -1};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i < 0; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_6) {
  std::vector<int> vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i > 0; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_7) {
  std::vector<int> vec = {2, 4, 6, 8};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; }),
      true);
}

TEST_F(AlgorithmsTest, AllOf_8) {
  std::vector<int> vec = {1, 3, 5, 7};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int i) { return i % 2 != 0; }),
      true);
}

TEST_F(AlgorithmsTest, AllOf_9) {
  std::vector<int> vec = {-1, -1, -1, 0};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i < 0; }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_10) {
  std::vector<int> vec = {-1, -1, -1, 0, 1};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i > 0; }),
            0);
}

TEST_F(AlgorithmsTest, AllOf_11) {
  std::vector<int> vec = {1, 3, 5, 7, 8};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; }),
      false);
}

TEST_F(AlgorithmsTest, AllOf_12) {
  std::vector<int> vec = {2, 4, 6, 7};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int i) { return i % 2 != 0; }),
      false);
}

TEST_F(AlgorithmsTest, AllOf_13) {
  std::vector<int> vec = {0, 0, 0, 0};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i == 0; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_14) {
  std::vector<int> vec = {1, 2, 3, 0};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i == 0; }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_15) {
  std::vector<int> vec = {11, 12, 13, 14};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i > 10; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_16) {
  std::vector<int> vec = {9, 10, 11, 12};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i > 10; }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_17) {
  std::vector<int> vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i < 10; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_18) {
  std::vector<int> vec = {8, 9, 10, 11};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i < 10; }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_19) {
  std::vector<int> vec = {0, 1, 2, 3};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_20) {
  std::vector<int> vec = {-1, 0, 1, 2};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }),
            0);
}

TEST_F(AlgorithmsTest, AllOf_21) {
  std::vector<int> vec = {0, -1, -2, -3};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i <= 0; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_22) {
  std::vector<int> vec = {1, 0, -1, -2};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i <= 0; }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_23) {
  std::vector<int> vec = {3, 6, 9, 12};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int i) { return i % 3 == 0; }),
      true);
}

TEST_F(AlgorithmsTest, AllOf_24) {
  std::vector<int> vec = {2, 5, 8, 9};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int i) { return i % 3 == 0; }),
      false);
}

TEST_F(AlgorithmsTest, AllOf_25) {
  std::vector<int> vec = {5, 10, 15, 20};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int i) { return i % 5 == 0; }),
      true);
}

TEST_F(AlgorithmsTest, AllOf_26) {
  std::vector<int> vec = {2, 5, 8, 12};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int i) { return i % 5 == 0; }),
      false);
}

TEST_F(AlgorithmsTest, AllOf_27) {
  std::vector<int> vec = {2, 3, 5, 7};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int i) {
                           if (i < 2) return false;
                           for (int j = 2; j < i; ++j) {
                             if (i % j == 0) return false;
                           }
                           return true;
                         }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_28) {
  std::vector<int> vec = {4, 6, 8, 11};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int i) {
                           if (i < 2) return false;
                           for (int j = 2; j < i; ++j) {
                             if (i % j == 0) return false;
                           }
                           return true;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_29) {
  std::vector<int> vec = {4, 9, 16, 25};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int i) {
                           int root = static_cast<int>(std::sqrt(i));
                           return (root * root == i);
                         }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_30) {
  std::vector<int> vec = {4, 9, 15, 25};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int i) {
                           int root = static_cast<int>(std::sqrt(i));
                           return (root * root == i);
                         }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_31) {
  std::vector<int> vec;
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i == 1; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_32) {
  std::vector<int> vec = {0, 0, 0, 0};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i == 0; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_33) {
  std::vector<int> vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i < 0; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_34) {
  std::vector<int> vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i > 0; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_35) {
  std::vector<int> vec = {7, 7, 7, 7};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i == 7; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_36) {
  std::vector<int> vec = {1, 2, 3, 4};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; }),
      false);
}

TEST_F(AlgorithmsTest, AllOf_37) {
  std::vector<int> vec = {10, 20, 30, 40};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int i) { return (i % 10 == 0) && (i > 5); }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_38) {
  std::vector<int> vec = {10, 20, 30, 41};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int i) { return (i % 10 == 0) && (i > 5); }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_39) {
  std::vector<char> vec = {'a', 'a', 'a', 'a'};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](char c) { return c == 'a'; }),
      true);
}

TEST_F(AlgorithmsTest, AllOf_40) {
  std::vector<char> vec = {'a', 'b', 'c', 'd'};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](char c) { return std::islower(c); }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_41) {
  std::vector<char> vec = {'A', 'B', 'C', 'D'};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](char c) { return std::isupper(c); }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_42) {
  std::vector<char> vec = {' ', '\t', '\n', '\r'};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](char c) { return std::isspace(c); }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_43) {
  std::vector<char> vec = {'!', '?', '.', ','};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](char c) { return std::ispunct(c); }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_44) {
  std::vector<int> vec = {25, 35, 45, 55};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int i) { return i >= 25 && i <= 55; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_45) {
  std::vector<int> vec = {25, 35, 45, 65};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int i) { return i >= 25 && i <= 55; }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_46) {
  std::vector<int> vec = {4, 8, 12, 16};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int i) { return i % 4 == 0; }),
      true);
}

TEST_F(AlgorithmsTest, AllOf_47) {
  std::vector<int> vec = {1, 2, 3, -4};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_48) {
  std::vector<int> vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [&](int i) {
                           auto it = std::find(vec.begin(), vec.end(), i);
                           return it == vec.end() ||
                                  it == std::find(std::next(it), vec.end(), i);
                         }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_49) {
  std::vector<int> vec = {1, 2, 3, 3};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [&](int i) {
                           auto it = std::find(vec.begin(), vec.end(), i);
                           return it == vec.end() ||
                                  it == std::find(std::next(it), vec.end(), i);
                         }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_50) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  std::unordered_set<std::string> validFruits = {"apple", "banana", "cherry"};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [&](const std::string& fruit) {
                           return validFruits.count(fruit) > 0;
                         }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_51) {
  std::vector<std::string> vec = {"apple", "banana", "orange"};
  std::unordered_set<std::string> validFruits = {"apple", "banana", "cherry"};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [&](const std::string& fruit) {
                           return validFruits.count(fruit) > 0;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_52) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](const std::string& str) { return !str.empty(); }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_53) {
  std::vector<std::string> vec = {"apple", "banana", ""};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](const std::string& str) { return !str.empty(); }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_54) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(),
                   [](const std::string& str) { return str.length() > 3; }),
      true);
}

TEST_F(AlgorithmsTest, AllOf_55) {
  std::vector<std::string> vec = {"apple", "banana", "cat"};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(),
                   [](const std::string& str) { return str.length() > 5; }),
      false);
}

TEST_F(AlgorithmsTest, AllOf_56) {
  std::vector<int> vec = {15, 30, 45, 60};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(),
                   [](int num) { return (num % 3 == 0) || (num % 5 == 0); }),
      true);
}

TEST_F(AlgorithmsTest, AllOf_57) {
  std::vector<int> vec = {15, 30, 47, 60};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(),
                   [](int num) { return (num % 3 == 0) || (num % 5 == 0); }),
      false);
}

TEST_F(AlgorithmsTest, AllOf_58) {
  std::vector<int*> vec = {new int(1), new int(2), new int(3)};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int* ptr) { return ptr != nullptr; }),
            true);
  for (auto ptr : vec) {
    delete ptr;
  }
}

TEST_F(AlgorithmsTest, AllOf_59) {
  std::vector<int*> vec = {new int(1), nullptr, new int(3)};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int* ptr) { return ptr != nullptr; }),
            false);
  for (auto ptr : vec) {
    delete ptr;
  }
}

enum class DayOfWeek {
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Sunday,
  Saturday
};

TEST_F(AlgorithmsTest, AllOf_60) {
  std::vector<DayOfWeek> vec = {DayOfWeek::Monday, DayOfWeek::Tuesday,
                                DayOfWeek::Wednesday};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](DayOfWeek day) {
                           return day >= DayOfWeek::Monday &&
                                  day <= DayOfWeek::Friday;
                         }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_61) {
  std::vector<DayOfWeek> vec = {DayOfWeek::Monday, DayOfWeek::Tuesday,
                                DayOfWeek::Saturday};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](DayOfWeek day) {
                           return day >= DayOfWeek::Monday &&
                                  day <= DayOfWeek::Friday;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_62) {
  std::vector<double> vec = {1.0, 1.0, 1.0, 1.0};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](double num) { return num == 1.0; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_63) {
  std::vector<double> vec = {1.0, 1.0, 1.0, 1.5};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](double num) { return num == 1.0; }),
            false);
}

struct Time {
  int hours;
  int minutes;
};

TEST_F(AlgorithmsTest, AllOf_64) {
  std::vector<Time> vec = {{9, 30}, {10, 45}, {11, 15}};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](const Time& time) {
                           return time.hours >= 9 && time.hours <= 12;
                         }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_65) {
  std::vector<Time> vec = {{9, 30}, {13, 45}, {11, 15}};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](const Time& time) {
                           return time.hours >= 9 && time.hours <= 12;
                         }),
            false);
}

struct Widget {
  int value;
  bool isValid() const { return value > 0 && value < 100; }
};

TEST_F(AlgorithmsTest, AllOf_66) {
  std::vector<Widget> vec = {{10}, {20}, {30}};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](const Widget& widget) { return widget.isValid(); }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_67) {
  std::vector<Widget> vec = {{10}, {200}, {30}};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](const Widget& widget) { return widget.isValid(); }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_68) {
  std::vector<int> vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [prev = INT_MIN](int current) mutable {
                           bool result = prev <= current;
                           prev = current;
                           return result;
                         }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_69) {
  std::vector<int> vec = {1, 3, 2, 4};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [prev = INT_MIN](int current) mutable {
                           bool result = prev <= current;
                           prev = current;
                           return result;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_70) {
  std::vector<int> vec = {4, 3, 2, 1};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [prev = INT_MAX](int current) mutable {
                           bool result = prev >= current;
                           prev = current;
                           return result;
                         }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_71) {
  std::vector<int> vec = {4, 3, 5, 1};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [prev = INT_MAX](int current) mutable {
                           bool result = prev >= current;
                           prev = current;
                           return result;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_72) {
  std::vector<std::string> vec = {"apple", "banana", "cherry", "date"};
  EXPECT_EQ(algo::all_of(
                vec.begin(), vec.end(),
                [prev = std::string("")](const std::string& current) mutable {
                  bool result = prev <= current;
                  prev = current;
                  return result;
                }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_73) {
  std::vector<std::string> vec = {"apple", "banana", "cherry", "avocado"};
  EXPECT_EQ(algo::all_of(
                vec.begin(), vec.end(),
                [prev = std::string("")](const std::string& current) mutable {
                  bool result = prev <= current;
                  prev = current;
                  return result;
                }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_74) {
  std::vector<int*> vec = {new int(1), new int(2), new int(3)};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int* ptr) { return ptr != nullptr; }),
            true);
  for (auto ptr : vec) {
    delete ptr;
  }
}

TEST_F(AlgorithmsTest, AllOf_75) {
  std::vector<int*> vec = {new int(1), nullptr, new int(3)};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int* ptr) { return ptr != nullptr; }),
            false);
  for (auto ptr : vec) {
    delete ptr;
  }
}

TEST_F(AlgorithmsTest, AllOf_76) {
  std::vector<int> vec = {2, 4, 6, 8};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int num) { return num % 2 == 0; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_77) {
  std::vector<int> vec = {2, 4, 7, 8};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int num) { return num % 2 == 0; }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_78) {
  std::vector<int> vec = {6, 7, 8, 9};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int num) { return num > 5; }),
      true);
}

TEST_F(AlgorithmsTest, AllOf_79) {
  std::vector<int> vec = {6, 7, 5, 9};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int num) { return num > 5; }),
      false);
}

TEST_F(AlgorithmsTest, AllOf_80) {
  std::vector<int> vec = {1, 2, 3, 4};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int num) { return num > 0; }),
      true);
}

TEST_F(AlgorithmsTest, AllOf_81) {
  std::vector<int> vec = {1, 2, -3, 4};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(), [](int num) { return num > 0; }),
      false);
}

TEST_F(AlgorithmsTest, AllOf_82) {
  std::vector<int> vec = {10, 20, 30, 40};
  int lowerBound = 10;
  int upperBound = 40;
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [lowerBound, upperBound](int num) {
                           return num >= lowerBound && num <= upperBound;
                         }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_83) {
  std::vector<int> vec = {10, 20, 30, 50};
  int lowerBound = 10;
  int upperBound = 40;
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [lowerBound, upperBound](int num) {
                           return num >= lowerBound && num <= upperBound;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_84) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(),
                   [](const std::string& str) { return str.length() > 3; }),
      true);
}

TEST_F(AlgorithmsTest, AllOf_85) {
  std::vector<std::string> vec = {"apple", "banana", "cat"};
  EXPECT_EQ(
      algo::all_of(vec.begin(), vec.end(),
                   [](const std::string& str) { return str.length() > 5; }),
      false);
}

TEST_F(AlgorithmsTest, AllOf_86) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [&](int num) { return (index++ % 2 == 0); }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_87) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [&](int num) { return (index++ % 2 == 1); }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_88) {
  std::vector<int> vec = {1, 1, 1, 1};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [&](int num) { return num == vec.front(); }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_89) {
  std::vector<int> vec = {1, 2, 1, 1};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [&](int num) { return num == vec.front(); }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_90) {
  std::vector<int> vec = {3, 6, 9, 12};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int num) { return num % 3 == 0; }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_91) {
  std::vector<int> vec = {3, 6, 8, 12};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int num) { return num % 3 == 0; }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_92) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  std::unordered_set<std::string> validFruits = {"apple", "banana", "cherry"};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [&](const std::string& fruit) {
                           return validFruits.count(fruit) > 0;
                         }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_93) {
  std::vector<std::string> vec = {"apple", "banana", "orange"};
  std::unordered_set<std::string> validFruits = {"apple", "banana", "cherry"};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [&](const std::string& fruit) {
                           return validFruits.count(fruit) > 0;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_94) {
  std::vector<std::string> vec = {"level", "radar", "madam"};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](const std::string& str) {
                           return std::equal(str.begin(),
                                             str.begin() + str.size() / 2,
                                             str.rbegin());
                         }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_95) {
  std::vector<std::string> vec = {"level", "radar", "hello"};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](const std::string& str) {
                           return std::equal(str.begin(),
                                             str.begin() + str.size() / 2,
                                             str.rbegin());
                         }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_96) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  EXPECT_EQ(algo::all_of(
                vec.begin(), vec.end(),
                [](const std::string& str) { return str.length() % 2 == 0; }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_97) {
  std::vector<std::string> vec = {"apple", "banana", "cat"};
  EXPECT_EQ(algo::all_of(
                vec.begin(), vec.end(),
                [](const std::string& str) { return str.length() % 2 == 0; }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_98) {
  std::vector<std::string> vec = {"john.doe@example.com",
                                  "jane_smith123@gmail.com"};
  EXPECT_EQ(algo::all_of(
                vec.begin(), vec.end(),
                [](const std::string& email) {
                  std::regex emailRegex(
                      R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b)");
                  return std::regex_match(email, emailRegex);
                }),
            true);
}

TEST_F(AlgorithmsTest, AllOf_99) {
  std::vector<std::string> vec = {"john.doe@example.com", "invalid_email"};
  EXPECT_EQ(algo::all_of(
                vec.begin(), vec.end(),
                [](const std::string& email) {
                  std::regex emailRegex(
                      R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b)");
                  return std::regex_match(email, emailRegex);
                }),
            false);
}

TEST_F(AlgorithmsTest, AllOf_100) {
  std::vector<int> vec = {2, 3, 5, 7, 11, 13};
  EXPECT_EQ(algo::all_of(vec.begin(), vec.end(),
                         [](int num) {
                           if (num < 2) return false;
                           for (int i = 2; i * i <= num; ++i) {
                             if (num % i == 0) return false;
                           }
                           return true;
                         }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_1) {
  std::vector<int> vec = {1, 1, 1, 1};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i == 2; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_2) {
  std::vector<int> vec = {1, 1, 1, 1, 2};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i == 2; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_3) {
  std::vector<int> vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i > 0; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_4) {
  std::vector<int> vec = {-1, -2, -3, -4, 5};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i > 0; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_5) {
  std::vector<int> vec = {2, 4, 6, 8};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 2 != 0; }),
      false);
}

TEST_F(AlgorithmsTest, AnyOf_6) {
  std::vector<int> vec = {2, 4, 6, 7};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 2 != 0; }),
      true);
}

TEST_F(AlgorithmsTest, AnyOf_7) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [&](int i) {
    bool result = index % 2 != 0;
    index++;
    return result;
  }), true);
}

TEST_F(AlgorithmsTest, AnyOf_8) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [&](int i) {
    bool result = index % 2 != 0;
    index++;
    return result;
  }), true);
}

TEST_F(AlgorithmsTest, AnyOf_9) {
  std::vector<int> vec = {-1, -3, -5, -7};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](int i) { return i > 0 && i % 2 == 0; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_10) {
  std::vector<int> vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i <= 0; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_11) {
  std::vector<int> vec = {2, 4, 5, 8};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 3 == 0; }),
      false);
}

TEST_F(AlgorithmsTest, AnyOf_12) {
  std::vector<int> vec = {2, 4, 6, 8};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 3 == 0; }),
      true);
}

TEST_F(AlgorithmsTest, AnyOf_13) {
  std::vector<int> vec = {11, 12, 13, 14};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i <= 10; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_14) {
  std::vector<int> vec = {11, 12, 13, 9};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i <= 10; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_15) {
  std::vector<char> vec = {'A', 'B', 'C', 'D'};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](char c) { return std::islower(c); }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_16) {
  std::vector<char> vec = {'A', 'B', 'c', 'D'};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](char c) { return std::islower(c); }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_17) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) { return str.empty(); }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_18) {
  std::vector<std::string> vec = {"apple", "banana", ""};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) { return str.empty(); }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_19) {
  std::vector<std::string> vec = {"apple", "banana", "cat"};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) {
                           return str.find('a') == std::string::npos;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_20) {
  std::vector<std::string> vec = {"apple", "banana", "cat"};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) {
                           return str.find('a') != std::string::npos;
                         }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_21) {
  std::vector<int> vec = {6, 7, 8, 9};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i <= 5; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_22) {
  std::vector<int> vec = {6, 7, 5, 9};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i <= 5; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_23) {
  std::vector<char> vec = {'A', 'B', 'C', 'D'};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](char c) { return std::islower(c); }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_24) {
  std::vector<char> vec = {'A', 'B', 'c', 'D'};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](char c) { return std::islower(c); }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_25) {
  std::vector<int> vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_26) {
  std::vector<int> vec = {-1, -2, -3, -4, 5};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_27) {
  std::vector<int> vec = {2, 4, 6, 8};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 2 != 0; }),
      false);
}

TEST_F(AlgorithmsTest, AnyOf_28) {
  std::vector<int> vec = {2, 4, 6, 7};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 2 != 0; }),
      true);
}

TEST_F(AlgorithmsTest, AnyOf_29) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [&](int i) {
    bool result = index % 2 != 0;
    index++;
    return result;
  }), true);
}

TEST_F(AlgorithmsTest, AnyOf_30) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [&](int i) {
    bool result = index % 2 != 0;
    index++;
    return result;
  }), true);
}

TEST_F(AlgorithmsTest, AnyOf_31) {
  std::list<std::string> lst = {"apple", "banana", "cherry"};
  EXPECT_EQ(algo::any_of(lst.begin(), lst.end(),
                         [](const std::string& str) { return str.empty(); }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_32) {
  std::list<std::string> lst = {"apple", "banana", ""};
  EXPECT_EQ(algo::any_of(lst.begin(), lst.end(),
                         [](const std::string& str) { return str.empty(); }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_33) {
  std::set<int> st = {3, 6, 9, 12};
  EXPECT_EQ(
      algo::any_of(st.begin(), st.end(), [](int i) { return i % 3 != 0; }),
      false);
}

TEST_F(AlgorithmsTest, AnyOf_34) {
  std::set<int> st = {3, 6, 8, 12};
  EXPECT_EQ(
      algo::any_of(st.begin(), st.end(), [](int i) { return i % 3 != 0; }),
      true);
}

// TEST_F(AlgorithmsTest, AnyOf_35) {
//   std::deque<int> dq = {1, 2, 3, 4};
//   EXPECT_EQ(algo::any_of(dq.begin(), dq.end(), [](int i, size_t index) {
//   return index % 2 != 0; }), false);
// }

// TEST_F(AlgorithmsTest, AnyOf_36) {
//   std::deque<int> dq = {1, 2, 3, 4};
//   EXPECT_EQ(algo::any_of(dq.begin(), dq.end(), [](int i, size_t index) {
//   return index % 2 != 1; }), true);
// }

TEST_F(AlgorithmsTest, AnyOf_37) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) { return str.empty(); }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_38) {
  std::vector<std::string> vec = {"apple", "banana", ""};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) { return str.empty(); }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_39) {
  std::vector<std::string> vec = {"apple", "banana", "cat"};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) {
                           return str.find('a') == std::string::npos;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_40) {
  std::vector<std::string> vec = {"apple", "banana", "cat"};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) {
                           return str.find('a') == std::string::npos;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_41) {
  std::vector<int> vec = {6, 7, 8, 9};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i <= 5; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_42) {
  std::vector<int> vec = {6, 7, 5, 9};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i <= 5; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_43) {
  std::vector<char> vec = {'A', 'B', 'C', 'D'};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](char c) { return std::islower(c); }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_44) {
  std::vector<char> vec = {'A', 'B', 'c', 'D'};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](char c) { return std::islower(c); }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_45) {
  std::vector<int> vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_46) {
  std::vector<int> vec = {-1, -2, -3, -4, 5};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_47) {
  std::vector<int> vec = {2, 4, 6, 8};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 2 != 0; }),
      false);
}

TEST_F(AlgorithmsTest, AnyOf_48) {
  std::vector<int> vec = {2, 4, 6, 7};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 2 != 0; }),
      true);
}

TEST_F(AlgorithmsTest, AnyOf_49) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [&](int i) mutable { return (index++ % 2) != 0; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_50) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [&](int i) mutable { return (index++ % 2) != 1; }),
            true);
}



TEST_F(AlgorithmsTest, AnyOf_51) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) { return str.empty(); }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_52) {
  std::vector<std::string> vec = {"apple", "banana", ""};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) { return str.empty(); }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_53) {
  std::vector<std::string> vec = {"apple", "banana", "cat"};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) {
                           return str.find('a') == std::string::npos;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_54) {
  std::vector<std::string> vec = {"apple", "banana", "cat"};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) {
                           return str.find('a') == std::string::npos;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_55) {
  std::vector<int> vec = {3, 6, 9, 12};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 3 != 0; }),
      false);
}

TEST_F(AlgorithmsTest, AnyOf_56) {
  std::vector<int> vec = {3, 6, 8, 12};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 3 != 0; }),
      true);
}

TEST_F(AlgorithmsTest, AnyOf_57) {
  std::vector<int> vec = {11, 12, 13, 14};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i <= 10; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_58) {
  std::vector<int> vec = {11, 12, 13, 9};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i <= 10; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_59) {
  std::vector<char> vec = {'A', 'B', 'C', 'D'};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](char c) { return std::islower(c); }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_60) {
  std::vector<char> vec = {'A', 'B', 'c', 'D'};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](char c) { return std::islower(c); }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_61) {
  std::vector<int> vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_62) {
  std::vector<int> vec = {-1, -2, -3, -4, 5};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_63) {
  std::vector<int> vec = {2, 4, 6, 8};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 2 != 0; }),
      false);
}

TEST_F(AlgorithmsTest, AnyOf_64) {
  std::vector<int> vec = {2, 4, 6, 7};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 2 != 0; }),
      true);
}

TEST_F(AlgorithmsTest, AnyOf_65) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [&](int i) mutable { return (index++ % 2) != 0; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_66) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [&](int i) mutable { return (index++ % 2) != 1; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_67) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) { return str.empty(); }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_68) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [&](int i) { return index % 2 != 0; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_69) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [&](int i) { return index % 2 != 1; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_70) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) { return str.empty(); }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_71) {
  std::vector<std::string> vec = {"apple", "banana", ""};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) { return str.empty(); }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_72) {
  std::vector<std::string> vec = {"apple", "banana", "cat"};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) {
                           return str.find('a') == std::string::npos;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_73) {
  std::vector<std::string> vec = {"apple", "banana", "cat"};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](const std::string& str) {
                           return str.find('a') == std::string::npos;
                         }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_74) {
  std::vector<int> vec = {3, 6, 9, 12};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 3 != 0; }),
      false);
}

TEST_F(AlgorithmsTest, AnyOf_75) {
  std::vector<int> vec = {3, 6, 8, 12};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 3 != 0; }),
      true);
}

TEST_F(AlgorithmsTest, AnyOf_76) {
  std::vector<int> vec = {11, 12, 13, 14};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i <= 10; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_77) {
  std::vector<int> vec = {11, 12, 13, 9};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i <= 10; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_78) {
  std::vector<char> vec = {'A', 'B', 'C', 'D'};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](char c) { return std::islower(c); }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_79) {
  std::vector<char> vec = {'A', 'B', 'c', 'D'};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [](char c) { return std::islower(c); }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_80) {
  std::vector<int> vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_81) {
  std::vector<int> vec = {-1, -2, -3, -4, 5};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_82) {
  std::vector<int> vec = {2, 4, 6, 8};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 2 != 0; }),
      false);
}

TEST_F(AlgorithmsTest, AnyOf_83) {
  std::vector<int> vec = {2, 4, 6, 7};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 2 != 0; }),
      true);
}

TEST_F(AlgorithmsTest, AnyOf_84) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [&](int i) { return index % 2 != 0; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_85) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [&](int i) { return index % 2 != 1; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_86) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(),
                   [](const std::string& str) { return str.length() > 5; }),
      true);
}

TEST_F(AlgorithmsTest, AnyOf_87) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(),
                   [](const std::string& str) { return str.length() <= 5; }),
      true);
}

TEST_F(AlgorithmsTest, AnyOf_88) {
  std::vector<int> vec = {1, 2, 3, 4};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [&](int i) { return i == static_cast<int>(index); }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_89) {
  std::vector<int> vec = {1, 2, 3, 3};
  size_t index = 0;
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(),
                         [&](int i) { return i == static_cast<int>(index); }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_90) {
  std::vector<double> vec = {1.5, 2.5, 3.5, 4.5};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](double d) { return d < 1.0; }),
      false);
}

TEST_F(AlgorithmsTest, AnyOf_91) {
  std::vector<double> vec = {1.5, 2.5, 3.5, 0.5};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](double d) { return d < 1.0; }),
      true);
}

TEST_F(AlgorithmsTest, AnyOf_92) {
  std::vector<int> vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i > 5; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_93) {
  std::vector<int> vec = {1, 2, 6, 4};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i > 5; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_94) {
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(),
                   [](const std::string& str) { return str == "banana"; }),
      true);
}

TEST_F(AlgorithmsTest, AnyOf_95) {
  std::vector<std::string> vec = {"apple", "mango", "cherry"};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(),
                   [](const std::string& str) { return str == "banana"; }),
      false);
}

TEST_F(AlgorithmsTest, AnyOf_96) {
  std::vector<int> vec = {1, 2, 3, 4};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; }),
      true);
}

TEST_F(AlgorithmsTest, AnyOf_97) {
  std::vector<int> vec = {1, 3, 5, 7};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; }),
      false);
}

TEST_F(AlgorithmsTest, AnyOf_98) {
  std::vector<int> vec = {1, 1, 1, 1};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i == 2; }),
            false);
}

TEST_F(AlgorithmsTest, AnyOf_99) {
  std::vector<int> vec = {1, 1, 1, 2};
  EXPECT_EQ(algo::any_of(vec.begin(), vec.end(), [](int i) { return i == 2; }),
            true);
}

TEST_F(AlgorithmsTest, AnyOf_100) {
  std::vector<double> vec = {1.0, 1.5, 2.0, 2.5};
  EXPECT_EQ(
      algo::any_of(vec.begin(), vec.end(), [](double d) { return d < 0.0; }),
      false);
}

TEST_F(AlgorithmsTest, NoneOf_1) {
  vec = {1, 1, 1, 1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 2; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_2) {
  vec = {1, 1, 1, 1, 2};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 2; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_3) {
  vec = {2, 2, 2, 2};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_4) {
  vec = {2, 2, 2, 2, 1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 1; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_5) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 5; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_6) {
  vec = {1, 2, 3, 4, 6};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 5; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_7) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_8) {
  vec = {-1, -2, -3, -4, 0};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_9) {
  vec = {};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_10) {
  vec = {1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 1; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_11) {
  vec = {1, 1, 1, 1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_12) {
  vec = {1, 1, 1, 1, 2};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 1; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_13) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 5; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_14) {
  vec = {1, 2, 3, 4, 5};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 5; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_15) {
  vec = {2, 2, 2, 2};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 2; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_16) {
  vec = {2, 2, 2, 2, 1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 2; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_17) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_18) {
  vec = {1, 2, 3, 4, -1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_19) {
  vec = {};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_20) {
  vec = {1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_21) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 5; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_22) {
  vec = {1, 2, 3, 4, 6};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 5; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_23) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_24) {
  vec = {-1, -2, -3, -4, 0};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_25) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_26) {
  vec = {1, 2, 3, 4, 0};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_27) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_28) {
  vec = {1, 2, 3, 4, 0};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_29) {
  vec = {1, 1, 1, 1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_30) {
  vec = {1, 1, 1, 1, 2};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 1; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_31) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 10; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_32) {
  vec = {1, 2, 3, 4, 11};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 10; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_33) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_34) {
  vec = {-1, -2, -3, -4, 0};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_35) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_36) {
  vec = {1, 3, 5, 7};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_37) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_38) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_39) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_40) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_41) {
  vec = {1, 1, 1, 1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_42) {
  vec = {1, 1, 1, 1, 2};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 1; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_43) {
  vec = {2, 2, 2, 2};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 2; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_44) {
  vec = {2, 2, 2, 2, 1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 2; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_45) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 5; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_46) {
  vec = {1, 2, 3, 4, 5};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 5; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_47) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_48) {
  vec = {-1, -2, -3, -4, 0};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_49) {
  vec = {};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_50) {
  vec = {1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_51) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 10; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_52) {
  vec = {1, 2, 3, 4, 11};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 10; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_53) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_54) {
  vec = {-1, -2, -3, -4, 0};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_55) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_56) {
  vec = {1, 3, 5, 7};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_57) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_58) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_59) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_60) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_61) {
  vec = {1, 1, 1, 1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_62) {
  vec = {1, 1, 1, 1, 2};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 1; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_63) {
  vec = {2, 2, 2, 2};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 2; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_64) {
  vec = {2, 2, 2, 2, 1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 2; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_65) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 5; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_66) {
  vec = {1, 2, 3, 4, 5};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 5; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_67) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_68) {
  vec = {-1, -2, -3, -4, 0};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_69) {
  vec = {};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_70) {
  vec = {1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_71) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 10; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_72) {
  vec = {1, 2, 3, 4, 11};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 10; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_73) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_74) {
  vec = {-1, -2, -3, -4, 0};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_75) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_76) {
  vec = {1, 3, 5, 7};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_77) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_78) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_79) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_80) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_81) {
  vec = {1, 1, 1, 1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_82) {
  vec = {1, 1, 1, 1, 2};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 1; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_83) {
  vec = {2, 2, 2, 2};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 2; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_84) {
  vec = {2, 2, 2, 2, 1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 2; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_85) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 5; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_86) {
  vec = {1, 2, 3, 4, 5};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 5; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_87) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_88) {
  vec = {-1, -2, -3, -4, 0};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i >= 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_89) {
  vec = {};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_90) {
  vec = {1};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i != 1; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_91) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 10; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_92) {
  vec = {1, 2, 3, 4, 11};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 10; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_93) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_94) {
  vec = {-1, -2, -3, -4, 0};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i == 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_95) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_96) {
  vec = {1, 3, 5, 7};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_97) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 0; }), true);
}

TEST_F(AlgorithmsTest, NoneOf_98) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i < 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_99) {
  vec = {1, 2, 3, 4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 0; }), false);
}

TEST_F(AlgorithmsTest, NoneOf_100) {
  vec = {-1, -2, -3, -4};
  EXPECT_EQ(algo::none_of(vec.begin(), vec.end(), [](int i) { return i > 0; }), true);
}

TEST_F(AlgorithmsTest, OneOf) {
  vec = {1, 1, 1, 1};
  EXPECT_EQ(algo::one_of(vec.begin(), vec.end(), [](int i) { return i == 2; }),
            false);

  vec.push_back(2);
  EXPECT_EQ(algo::one_of(vec.begin(), vec.end(), [](int i) { return i == 2; }),
            true);

  vec.push_back(2);
  EXPECT_EQ(algo::one_of(vec.begin(), vec.end(), [](int i) { return i == 2; }),
            false);
}

TEST_F(AlgorithmsTest, IsSorted) {
  vec = {1, 2, 3, 4, 3};
  EXPECT_EQ(algo::is_sorted(vec.begin(), vec.end()), false);

  vec.pop_back();
  EXPECT_EQ(algo::is_sorted(vec.begin(), vec.end()), true);

  vec = {5, 4, 3, 2, 1};
  EXPECT_EQ(algo::is_sorted(vec.begin(), vec.end(),
                            [](int a, int b) { return a > b; }),
            true);

  vec.push_back(5);
  EXPECT_EQ(algo::is_sorted(vec.begin(), vec.end(),
                            [](int a, int b) { return a > b; }),
            false);
}

TEST_F(AlgorithmsTest, IsPartitioned) {
  vec = {1, 2, 3};
  EXPECT_EQ(algo::is_partitioned(vec.begin(), vec.end(),
                                 [](int a) { return a == 1; }),
            true);

  vec = {1, 1, 2, 3};
  EXPECT_EQ(algo::is_partitioned(vec.begin(), vec.end(),
                                 [](int a) { return a != 1; }),
            true);

  vec = {2, 1, 2, 3};
  EXPECT_EQ(algo::is_partitioned(vec.begin(), vec.end(),
                                 [](int a) { return a == 1; }),
            false);
}

TEST_F(AlgorithmsTest, FindNot) {
  vec = {1, 2, 1, 1};
  EXPECT_EQ(*(algo::find_not(vec.begin(), vec.end(), 1)), 2);

  vec = {1, 1, 1, 1};
  EXPECT_EQ(algo::find_not(vec.begin(), vec.end(), 1), vec.end());
}

TEST_F(AlgorithmsTest, FindBackward) {
  vec = {1, 2, 1, 1};
  EXPECT_EQ(*(algo::find_backward(vec.begin(), vec.end(), 1)), 1);

  vec = {1, 1, 1, 1};
  EXPECT_EQ(algo::find_backward(vec.begin(), vec.end(), 2), vec.begin());
}

TEST_F(AlgorithmsTest, IsPalindrome) {
  str = "abba";
  EXPECT_EQ(algo::is_palindrome(str.begin(), str.end()), true);

  str = "notabba";
  EXPECT_EQ(algo::is_palindrome(str.begin(), str.end()), false);

  str = "racecar";
  EXPECT_EQ(algo::is_palindrome(str.begin(), str.end()), true);
}

TEST_F(AlgorithmsTest, xrange) {
  vec = {0, 1, 2, 3, 4};

  auto x = algo::xrange(0, 5);
  std::vector<int> vec_test_int = {x.begin(), x.end()};
  EXPECT_EQ(vec, vec_test_int);

  std::vector<float> vec_float = {1.5, 2.5, 3.5, 4.5};

  auto y = algo::xrange(1.5, 5.5);
  std::vector<float> vec_test_float = {y.begin(), y.end()};
  EXPECT_EQ(vec_float, vec_test_float);

  std::vector<float> vec_step = {0.0, 0.5, 1.0, 1.5};

  auto z = algo::xrange(0.0, 2.0, 0.5);
  std::vector<float> vec_test_step = {z.begin(), z.end()};
  EXPECT_EQ(vec_step, vec_test_step);
}

TEST_F(AlgorithmsTest, zip) {
  std::vector<int> l = {1, 2, 3, 4, 5};
  std::vector<char> v = {'a', 'b', 'c', 'd'};

  int iteration = 0;
  for (auto value : algo::zip(l, v)) {
    EXPECT_EQ(value.first, l[iteration]);
    EXPECT_EQ(value.second, v[iteration]);
    iteration++;
  }
}

bool allElementsSatisfyPredicate(const std::vector<int>& vec, int target) {
  for (int i : vec) {
    if (i != target) {
      return false;
    }
  }
  return true;
}
