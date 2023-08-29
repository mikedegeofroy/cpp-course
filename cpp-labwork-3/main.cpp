#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// A possible way of making it better is 4bpp instead of 8bpp (find a way to work with bits)

// TO-DO
// Fix input sequence
// Enlarge grid?

struct Initializer {

  // Matrix settings
  
  size_t width = 5;
  size_t height = 5;
  size_t frequency = 0;
  size_t iterations = 0;
  bool infinite = true;
  bool verbose = false;
  std::vector<std::vector<uint64_t>> grid;

  // I/O

  std::string input = "input.tsv";
  std::string output = "output.bmp";

  // Helper Functions

  Initializer(int argc, char **argv);
  void printGrid(int k = -1);
  void generateImage(int k = -1);
};

int main(int argc, char **argv) {
  Initializer options(argc, argv);

  std::vector<std::vector<uint64_t>>& grid = options.grid;

  int k;
  bool stable;

  for (k = 0, stable = false; (k < options.iterations || options.infinite ) && !stable; k++) {

    stable = true;

    for (int y = 0; y < grid.size(); y++) {  // y axis

      for (int x = 0; x < grid[y].size(); x++) {  // x axis

        if (grid[y][x] >= 4) {
          stable = false;

          grid[y][x] -= 4;

          // The if functions are to possibly implement a grid expansion

          if (y + 1 >= grid.size()) {
            // std::cout << "+y overflow: " << y + 1 << " " << x << std::endl;
          } else {
            grid[y + 1][x]++;
          }

          if (y - 1 < 0) {
            // std::cout << "-y overflow: " << y - 1 << " " << x << std::endl;
          } else {
            grid[y - 1][x]++;
          }

          if (x + 1 >= grid[y].size()) {
            // std::cout << "+x overflow: " << y << " " << x + 1 << std::endl;
          } else {
            grid[y][x + 1]++;
          }

          if (x - 1 < 0) {
            // std::cout << "-x overflow: " << y << " " << x - 1 << std::endl;
          } else {
            grid[y][x - 1]++;
          }

        }
      }
    }

    if(options.verbose){
      std::cout << "Iteration: " << k << "\nInfinite: " << options.infinite << "\nStable: " << stable << "\n";
    }

    // Outputing every options.frequency photo

    if(options.frequency != 0 && k % options.frequency == 0){
      options.generateImage(k);
    }


  }

  options.generateImage(k);

}

void Initializer::printGrid(int k){

  if(k >= 0){
    std::cout << "Iteration: " << k << std::endl;
  }

  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      std::cout << grid[i][j] << " ";
    }
    std::cout << std::endl;
  }

}

void Initializer::generateImage(int k){

  FILE* imageFile;

  if(k >= 0){
    imageFile = fopen(( std::to_string(k) + ".bmp").c_str(), "wb");
  } else {
    imageFile = fopen(output.c_str(), "wb");
  }

  int paddingSize = (4 - (width) % 4) % 4;

  int fileSize = 14 + 56 + ( height * (width + paddingSize));

  static unsigned char fileHeader[] = {
    0, 0, // BM
    0, 0, 0, 0, // File Size
    0, 0, 0, 0, // Reserved for god knows what
    0, 0, 0, 0, // Start of pixel data (14 + 56)
  };

  fileHeader[0] = (unsigned char)('B');
  fileHeader[1] = (unsigned char)('M');
  fileHeader[2] = (unsigned char)(fileSize);
  fileHeader[3] = (unsigned char)(fileSize >> 8);
  fileHeader[4] = (unsigned char)(fileSize >> 16);
  fileHeader[5] = (unsigned char)(fileSize >> 24);
  fileHeader[10] = (unsigned char)(70);

  fwrite(fileHeader, 1, 14, imageFile);

  static unsigned char dibHeader[] = {
    0, 0, 0, 0, // Size
    0, 0, 0, 0, // Width
    0, 0, 0, 0, // Height
    0, 0, // Planes
    0, 0, // Bit Count
    0, 0, 0, 0, // Compression
    0, 0, 0, 0, // Image Size
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0, // Colours Used (ammount)
    0, 0, 0, 0, // Important Colors
    0, 0, 0, 0, // Colour Index 0 // b g r 
    0, 0, 0, 0, // Colour Index 1 // b g r
    0, 0, 0, 0, // Colour Index 2 // b g r
    0, 0, 0, 0, // Colour Index 3 // b g r
    0, 0, 0, 0, // Colour Index 4 // b g r
  };

  dibHeader[0] = (unsigned char)(40);
  dibHeader[4] = (unsigned char)(width);
  dibHeader[5] = (unsigned char)(width >> 8);
  dibHeader[6] = (unsigned char)(width >> 16);
  dibHeader[7] = (unsigned char)(width >> 24);
  dibHeader[8] = (unsigned char)(height);
  dibHeader[9] = (unsigned char)(height >> 8);
  dibHeader[10] = (unsigned char)(height >> 16);
  dibHeader[11] = (unsigned char)(height >> 24);
  dibHeader[12] = (unsigned char)(1);
  dibHeader[14] = (unsigned char)(8);
  dibHeader[32] = (unsigned char)(5);
  dibHeader[40] = (unsigned char)(255); // white g
  dibHeader[41] = (unsigned char)(255); // white b
  dibHeader[42] = (unsigned char)(255); // white r
  dibHeader[45] = (unsigned char)(255); // green g
  dibHeader[48] = (unsigned char)(255); // purple
  dibHeader[50] = (unsigned char)(255); // purple
  dibHeader[53] = (unsigned char)(255); // yellow
  dibHeader[54] = (unsigned char)(255); // yellow

  // 4 bits per pixel

  fwrite(dibHeader, 1, 56, imageFile);

  unsigned char padding[3] = {0, 0, 0};

  for (int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {

      unsigned char c;

      c = static_cast<char>(grid[i][j]);

      unsigned char pixel[1] = { c };

      fwrite(pixel, 1, 1, imageFile);
    }
    fwrite(padding, 1, paddingSize, imageFile);
  }

  fclose(imageFile);

  std::cout << "Exported: " << ( std::to_string(k) + ".bmp").c_str() << std::endl;


}

Initializer::Initializer(int argc, char **argv) {

  for (size_t i = 0; i < argc; i++) {
    if (std::strcmp(argv[i], "-l") == 0 ||
        std::strcmp(argv[i], "--length") == 0) {
      height = std::stoi(argv[++i]);
    }
    if (std::strcmp(argv[i], "-w") == 0 ||
        std::strcmp(argv[i], "--width") == 0) {
      width = std::stoi(argv[++i]);
    }
    if (std::strcmp(argv[i], "-i") == 0 ||
        std::strcmp(argv[i], "--input") == 0) {
      input = argv[++i];
    }
    if (std::strcmp(argv[i], "-o") == 0 ||
        std::strcmp(argv[i], "--output") == 0) {
      output = argv[++i];
    }
    if (std::strcmp(argv[i], "-m") == 0 ||
        std::strcmp(argv[i], "--max-iter") == 0) {
      iterations = std::stoi(argv[++i]);
      infinite = false;
    }
    if (std::strcmp(argv[i], "-f") == 0 ||
        std::strcmp(argv[i], "--freq") == 0) {
      frequency = std::stoi(argv[++i]);
    }
    if (std::strcmp(argv[i], "-v") == 0 ||
        std::strcmp(argv[i], "--verbose") == 0) {
      verbose = true;
    }
  }

  std::vector<uint64_t> row(width);

  for(int i = 0; i < height; i++){
    grid.push_back(row);
  }

  std::ifstream file( input );
  int x, y;
  uint32_t value;
  while( file >> x >> y >> value){
    grid[y][x] = value;
  }

}