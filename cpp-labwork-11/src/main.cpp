#include <iostream>
#include <list>
#include <vector>

#include "lib/algorithms.h"

int main() {
  std::list<int> l = {1, 2, 3, 4, 5};
  std::vector<char> v = {'a', 'b', 'c', 'd'};

  for (auto value : algo::zip(l, v)) {
    std::cout << value.first << " " << value.second << std::endl;
  }
}