#include <iostream>
#include <vector>

#include <lib/frame.h>

int main(int argc, char** argv) {

  ID3v2 parser;

  parser.Read(argv[1]);

  parser.Out();

  return 0;

}
