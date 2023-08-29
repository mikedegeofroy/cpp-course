#include <iostream>
#include <string>

#include <lib/CircularBuffer.h>

int main() {
  ExtCircularBuffer<std::string> buffer(10);

  buffer.push_back("Banana 1");
  buffer.push_back("Banana 2");
  buffer.push_back("Banana 3");
  buffer.push_back("Banana 4");
  buffer.push_back("Banana 3");

  buffer.resize(3);

  for (int i = 0; i < buffer.size(); ++i) {
    std::cout << buffer[i] << "\n";
  }

}