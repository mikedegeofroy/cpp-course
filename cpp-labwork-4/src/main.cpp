#include "lib/cliparser.h"
#include "lib/hafarchiver.h"

#include <vector>
#include <string>

int main(int argc, char** argv) {

  cliparser.addParam("-f", "--files");
  cliparser.addParam("-c", "--create");
  cliparser.addParam("-x", "--extract");
  cliparser.addParam("-l", "--list");
  cliparser.addParam("-a", "--append");
  cliparser.addParam("-A", "--concatenate");
  cliparser.addParam("-d", "--delete");
  cliparser.addParam("-r", "--raw");

  cliparser.parse(argc, argv);

  std::vector<std::string> arguments;
  
  if (cliparser.getParam("-c").size() == 1) {
  
    arguments = cliparser.getParam("-f");

    arguments.erase(arguments.begin());

    if (cliparser.getParam("-r").size() > 0) {
      EncodeRaw(arguments);
    } else {
      Encode(arguments);
    }
  }

  arguments = cliparser.getParam("-x");

  if (arguments.size() > 1) {


    for(int i = 0; i < arguments.size(); i++){
      std::cout << arguments[i] << "\n";
    }

    arguments.erase(arguments.begin());

    if (cliparser.getParam("-r").size() > 0) {
      DecodeRaw(arguments);
    } else {
      Decode(arguments);
    }
  }

  arguments = cliparser.getParam("-l");

  if (arguments.size() > 1) {

    arguments.erase(arguments.begin());

    listFiles(arguments[0]);
  }

  arguments = cliparser.getParam("-a");

  if (arguments.size() > 2) {

    arguments.erase(arguments.begin());

    Append(arguments);
  }

  arguments = cliparser.getParam("-d");

  if (arguments.size() > 2) {

    arguments.erase(arguments.begin());

    Delete(arguments);
    
  }

  arguments = cliparser.getParam("-A");

  if (arguments.size() > 2) {

    arguments.erase(arguments.begin());

    Concat(arguments);
    
  }

}