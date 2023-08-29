#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include <map>


class Cliparser {

  // A collection of arguments that can be accessed by a index

  std::vector<std::string> tokens;

  std::vector<std::string> known_commands;

  public:

    void parse(int argc, char** argv){

      for (int i = 1; i < argc;){

        char *token = strtok(argv[i], "=");
        
        while (token != NULL) {

          if(argv[i][0] == '-' && std::find(known_commands.begin(), known_commands.end(), argv[i]) == known_commands.end()) {
            std::cout << "Unknown argument: " << argv[i] << std::endl;
            exit( 2 );
          }
        
          tokens.push_back(std::string(token));

          token = strtok(NULL, "=");

        }

        i++;

      }

    }

    void getTokens(){
      for(int x = 0; x < tokens.size(); x++){
        std::cout << tokens[x] << " ";
      }
      std::cout << "\n";
    }

    std::vector<std::string> getParam(std::string option) {

      std::vector<std::string> output;

      // get known commands (short and long)

      std::vector<std::string> commands;
      
      auto test = std::find(known_commands.begin(), known_commands.end(), option);

      if(test != known_commands.end()){
        int index = test - known_commands.begin();

        if(known_commands[index][1] == '-'){
          commands.push_back(known_commands[index - 1]);
          commands.push_back(known_commands[index]);
        } else {
          commands.push_back(known_commands[index]);
          commands.push_back(known_commands[index + 1]);
        }
      }

      std::vector<std::string>::const_iterator itr;

      for(int i = 0; i < commands.size(); i++){

        itr = std::find(tokens.begin(), tokens.end(), commands[i]);

        if(itr != tokens.end()){

          output.push_back(*itr);
          std::advance(itr, 1);

          while(itr != tokens.end() && (*itr)[0] != '-' ){
            output.push_back(*itr);
            std::advance(itr, 1);
          }

        }
      }

      return output;

    }

    void addParam(std::string short_option, std::string option){
      known_commands.push_back(short_option);
      known_commands.push_back(option);
    }

};

Cliparser cliparser;