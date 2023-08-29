#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

enum Flag {
  lines_flag,
  bytes_flag,
  words_flag,
  chars_flag,
  help_flag
};

class Options {
  public:
    bool lines;
    bool bytes;
    bool words;
    bool chars;
    bool modified;
    bool help;
    std::map<std::string, Flag> Flags;

    Options(){
      lines = false;
      bytes = false;
      words = false;
      chars = false;
      modified = false;

      // This is for the switch case (probably bad practice)

      Flags["lines"] = lines_flag;
      Flags["bytes"] = bytes_flag;
      Flags["words"] = words_flag;
      Flags["chars"] = chars_flag;
      Flags["help"] = help_flag;

      Flags["l"] = lines_flag;
      Flags["c"] = bytes_flag;
      Flags["w"] = words_flag;
      Flags["m"] = chars_flag;
      Flags["h"] = help_flag;
    }
};

int HandleFile(const std::string& file_name, Options& options) {

  std::ostringstream oss;
  std::string output;

  std::ifstream inFile(file_name, std::ios::binary);

  if (!options.modified || options.lines || options.words || options.chars) {

    size_t line_count = 0;
    size_t char_count = 0;
    size_t word_count = 0;
    std::string line;
    std::string word;
  
    while (getline(inFile, line)) {
        ++line_count;
        char_count += line.length();
        std::stringstream lineStream(line);
        while(getline(lineStream, line, ' ')) {
            ++word_count;
        }
    }

    if (options.lines) {
      oss << output << line_count << " ";
    } 
    if (options.words) {
      oss << output << word_count << " ";
    } 
    if (options.chars) {
      oss << output << char_count << " ";
    } 
    if (!options.modified) {
      oss << output << line_count << " ";
      oss << output << word_count << " ";
    }
    
  }

  // Find out why this works
  if (!options.modified || options.bytes) {

    std::streampos byte_count = 0;

    std::ifstream inFile( file_name, std::ios::binary );

    inFile.seekg( 0, std::ios::beg );

    byte_count = inFile.tellg();

    inFile.seekg( 0, std::ios::end );

    byte_count = inFile.tellg() - byte_count;

    oss << output << byte_count << " ";

  }

  oss << output << file_name;

  std::cout << oss.str() << std::endl;

  return 0;
}

void Help(){
    std::cout << std::endl;
    std::cout << "\033[1;31m WordCount \033[0m:  A simple utility for counting lines, words and characters." << std::endl;
    std::cout << std::endl;
    std::cout << "usage:  " << std::endl;
    std::cout << "            wordcount [ arguments ] [ file.. ]\n" << std::endl;
    std::cout << "arguments:  " << std::endl;
    std::cout << "            " << "-l --lines display line count in file" << std::endl;
    std::cout << "            " << "-m --chars display line count in file" << std::endl;
    std::cout << "            " << "-w --words display word count in file" << std::endl;
    std::cout << "            " << "-c --bytes display file size" << std::endl;
    std::cout << "            " << "-h --help display this page" << std::endl;
}

int main(int argc, char **argv) {

  Options options;

  std::vector<std::string> files;

  for (int i = 1; i < argc; i++) {
    if (argv[i][1] == '-') {
      // Large flag

      // This is probably bad practice, but I did it for the sake of cleaner code, it gets rid of the "--" before the word, so the input inside Initialize() would be cleaner.

      std::string temp;

      for(int j = 2; j < strlen(argv[i]); j++){
        temp.push_back(argv[i][j]);
      }

      options.modified = true;

      switch (options.Flags[temp]) {
        case lines_flag:
          options.lines = true;
          break;
        case bytes_flag:
          options.bytes = true;
          break;
        case words_flag:
          options.words = true;
          break;
        case chars_flag:
          options.chars = true;
          break;
        default:
          options.help = true;
      }

    }
    else if (argv[i][0] == '-') {
      // Small flag

      options.modified = true;

      // For each argument under mini flag it will call the switch case

      for (int j = 1; j < strlen(argv[i]); j++) {

        std::string temp;
        temp.push_back(argv[i][j]);

        switch(options.Flags[temp]) {
          case lines_flag:
            options.lines = true;
            break;
          case bytes_flag:
            options.bytes = true;
            break;
          case words_flag:
            options.words = true;
            break;
          case chars_flag:
            options.chars = true;
            break;
          default:
            options.help = true;
        }
      }

    } else {
      files.push_back(argv[i]);
    }
  }

  // Make sure to output help if the command is misused 

  if (files.size() == 0) {
    options.help = true;
  }


  // For each directory we want to execute a list of functions based on the options

  if (!options.help) {
    for (int i = 0; i < files.size(); i++) {
      HandleFile(files[i], options);
    }
  } else {
    // Help page
    Help();
  }

  return 0;
}