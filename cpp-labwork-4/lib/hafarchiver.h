#include <bitset>
#include <fstream>
#include <iostream>
#include <vector>

// file -> 

// Constants

const int block_size = 16;

// Helper functions

template <size_t N1, size_t N2>
std::bitset<N1 + N2> concat(const std::bitset<N1> &b1,
                            const std::bitset<N2> &b2) {
  std::string s1 = b1.to_string();
  std::string s2 = b2.to_string();
  return std::bitset<N1 + N2>(s1 + s2);
}

template <std::size_t N>
void reverse(std::bitset<N> &b) {
  for (std::size_t i = 0; i < N / 2; ++i) {
    bool t = b[i];
    b[i] = b[N - i - 1];
    b[N - i - 1] = t;
  }
}

void printProgress(double percentage, std::string filename) {
  int val = (int)(percentage * 100);
  std::cout << "\r" << filename << " " << val << "%" << std::flush;
}

// Helper function, writes a (8 bitset)
void writeByte(std::bitset<8> buffer, std::ofstream *output) {
  char ch = 0;
  for (int j = 0; j < 8; j++) {
    ch |= (buffer[j] << (8 - j - 1));
  }
  output->write(&ch, sizeof(ch));
}

void writeChunk(std::bitset<16> chunk, std::ofstream *output) {
  for (int i = 0; i < 16 / 8; i++) {
    char ch = 0;
    for (int j = 0; j < 8; j++) {
      int k = i * 8 + j;
      ch |= (chunk[k] << (8 - j - 1));
    }
    output->write(&ch, sizeof(ch));
    ;
  }
}

// Helper function, reads 1 chunk from file (16 bits)
std::bitset<16> readChunk(std::ifstream *file) {
  std::bitset<8> buffer1;
  std::bitset<8> buffer2;

  file->read((char *)&buffer1, 1);
  reverse(buffer1);

  file->read((char *)&buffer2, 1);
  reverse(buffer2);

  return concat(buffer2, buffer1);
}

// Actual code

// Encodes a chunk of 8 bits and writes to file a 16 bit chunk.
void encodeChunk(std::bitset<8> buffer, std::ofstream *output) {
  std::bitset<block_size> chunk;

  reverse(buffer);

  size_t variable = 1;
  // setting non parity bits

  for (int i = 1, k = 0; i < block_size; i++) {
    if (i == variable) {
      chunk[i] = 0;
      variable *= 2;
    } else {
      chunk[i] = buffer[k];
      k++;
    }
  }

  // setting parity bits

  int parity = 0;

  for (int i = 1; i < block_size; i *= 2) {
    parity = 0;

    for (int j = 0; j < block_size;) {
      j += i;

      for (int k = j; k < j + i; k++) {
        parity ^= chunk[k];
      }

      j += i;
    }

    chunk[i] = parity;
  }

  // pos 0 partiy bit

  parity = 0;

  for (int i = 0; i < block_size; i++) {
    parity ^= chunk[i];
  }

  chunk[0] = parity;

  for (int i = 0; i < block_size / 8; i++) {
    char ch = 0;
    for (int j = 0; j < 8; j++) {
      int k = i * 8 + j;
      ch |= (chunk[k] << (8 - j - 1));
    }
    output->write(&ch, sizeof(ch));
    ;
  }
}

// Decodes a chunk of 16 bits and returns a 8 bit chunk.
std::bitset<8> decodeChunk(std::bitset<16> chunk) {
  int parity = 0;

  std::bitset<8> buffer;

  for (int i = 0; i < 16; i++) {
    if (chunk[i] == 1) {
      parity ^= i;
    }
  }

  if (parity != 0) {
    std::cout << "The file may be damaged" << "\n";
    exit(2);
  }

  int variable = 1;

  for (int i = 1, k = 0; i < block_size; i++) {
    if (i == variable) {
      variable *= 2;
    } else {
      buffer[k] = chunk[i];
      k++;
    }
  }

  return buffer;
}

// Encodes a set of files into 1 (input_files[0])
void Encode(std::vector<std::string> input_files) {
  std::ofstream output(input_files[0], std::ios::binary);

  for (int file_count = 1; file_count < input_files.size(); file_count++) {
    std::ifstream file(input_files[file_count], std::ios::binary);

    size_t name_size = input_files[file_count].size();

    file.seekg(0, std::ios::end);
    int file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::bitset<8> null;

    int chunk_size = block_size;
    int chunk_count = (file_size + 1) / 2;

    int header_size = name_size * 8 + 4 * 8;

    // Encode filename
    for (int i = 0; i < name_size; i++) {
      std::bitset<8> buffer(input_files[file_count][i]);
      encodeChunk(buffer, &output);
    }

    encodeChunk(null, &output);

    std::bitset<32> chunk_b(chunk_count);

    for (int i = 0; i < 4; i++) {
      std::bitset<8> buffer;
      for (int j = 0; j < 8; j++) {
        buffer[j] = chunk_b[i * 8 + j];
      }
      encodeChunk(buffer, &output);
    }

    encodeChunk(null, &output);

    std::bitset<8> buffer;

    int counter = 0;

    while (!file.eof()) {
      file.read((char *)&buffer, 1);

      if (file.eof()) break;

      encodeChunk(buffer, &output);

      if (counter % 5 == 0) {
        printProgress(counter / chunk_count, input_files[file_count]);
      }

      counter++;
    }

    encodeChunk(null, &output);

    std::cout << "\n";
  }
}

void EncodeRaw(std::vector<std::string> input_files) {
  std::ofstream output("input.raw", std::ios::binary);

  for (int file_count = 1; file_count < input_files.size(); file_count++) {
    std::ifstream file(input_files[file_count], std::ios::binary);

    size_t name_size = input_files[file_count].size();

    file.seekg(0, std::ios::end);
    int file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::bitset<8> null;

    int chunk_size = block_size;
    int chunk_count = (file_size + 1) / 2;

    int header_size = name_size * 8 + 4 * 8;

    // Encode filename
    for (int i = 0; i < name_size; i++) {
      std::bitset<8> buffer(input_files[file_count][i]);
      reverse(buffer);
      writeByte(buffer, &output);
    }

    writeByte(null, &output);

    std::bitset<32> chunk_b(chunk_count);

    for (int i = 0; i < 4; i++) {
      std::bitset<8> buffer;
      for (int j = 0; j < 8; j++) {
        buffer[j] = chunk_b[i * 8 + j];
      }
      reverse(buffer);
      writeByte(buffer, &output);
    }

    writeByte(null, &output);

    std::bitset<8> buffer;

    int counter = 0;

    while (!file.eof()) {
      file.read((char *)&buffer, 1);

      if (file.eof()) break;

      reverse(buffer);
      writeByte(buffer, &output);

      if (counter % 5 == 0) {
        printProgress(counter / chunk_count, input_files[file_count]);
      }

      counter++;
    }

    writeByte(null, &output);

    std::cout << "\n";
  }
}

// Decodes a hamrc file
void Decode(std::vector<std::string> input_file) {
  std::ifstream file(input_file[0], std::ios::binary);

  std::bitset<block_size> chunk;
  std::bitset<8> buffer2;
  std::bitset<8> buffer1;

  while (!file.eof()) {
    std::string filename;

    chunk = readChunk(&file);
    if (!chunk.none()) {
      file.seekg(-2, std::ios::cur);
    }

    for (std::bitset<8> buffer(1); !buffer.none();) {
      chunk = readChunk(&file);
      buffer = decodeChunk(chunk);
      reverse(buffer);

      filename += (char)buffer.to_ulong();
    }

    std::bitset<32> chunk_count;

    int i = 0;
    for (std::bitset<8> buffer(1); !buffer.none() || i < 5;) {
      chunk = readChunk(&file);
      buffer = decodeChunk(chunk);
      reverse(buffer);

      for (int j = 0; j < 8; j++) {
        chunk_count[i * 8 + j] = buffer[j];
      }
      i++;
    }

    // get chunk count and read x chunks
    std::ofstream output(filename, std::ios::binary);

    for (int i = 0; i < chunk_count.to_ulong() * 2; i++) {
      // if(i % 10 == 0){
      //   printProgress( (1.0 * i) / (1.0 * chunk_count.to_ulong() * 2),
      //   filename );
      // }

      file.read((char *)&buffer1, 1);
      reverse(buffer1);

      file.read((char *)&buffer2, 1);
      reverse(buffer2);

      chunk = concat(buffer2, buffer1);

      std::bitset<8> buffer = decodeChunk(chunk);

      writeByte(buffer, &output);
    }

    // printProgress(1.0, filename);

    // std::cout << "\n";

    if (file.eof()) break;
  }
}

void DecodeRaw(std::vector<std::string> input_file) {
  std::ifstream file(input_file[0], std::ios::binary);

  std::bitset<block_size> chunk;
  std::bitset<8> buffer2;
  std::bitset<8> buffer1;

  std::ofstream output("output.raw", std::ios::binary);

  int counter = 0;

  while (!file.eof()) {
    counter++;

    file.read((char *)&buffer1, 1);
    reverse(buffer1);

    file.read((char *)&buffer2, 1);
    reverse(buffer2);

    chunk = concat(buffer2, buffer1);

    std::bitset<8> buffer = decodeChunk(chunk);

    writeByte(buffer, &output);

    if (file.eof()) break;
  }

  std::cout << counter << "\n";
}
// Lits files inside archive
void listFiles(std::string input_filename) {
  std::ifstream file(input_filename, std::ios::binary);

  std::bitset<block_size> chunk;
  std::bitset<8> buffer;

  while (!file.eof()) {
    std::string filename;

    chunk = readChunk(&file);
    if (!chunk.none()) {
      file.seekg(-2, std::ios::cur);
    }

    for (std::bitset<8> buffer(1); !buffer.none();) {
      chunk = readChunk(&file);
      buffer = decodeChunk(chunk);
      reverse(buffer);

      filename += (char)buffer.to_ulong();
    }

    std::cout << filename << " ";

    std::bitset<32> chunk_count;

    int i = 0;

    for (std::bitset<8> buffer(1); i < 4;) {
      chunk = readChunk(&file);

      buffer = decodeChunk(chunk);
      reverse(buffer);

      for (int j = 0; j < 8; j++) {
        chunk_count[i * 8 + j] = buffer[j];
      }
      i++;
    }

    std::cout << chunk_count.to_ulong() << "\n";

    file.ignore(2);

    file.ignore((chunk_count.to_ulong() * 4) + 2);

    if (file.eof()) break;
  }
}

// Appends a file to a archive
void Append(std::vector<std::string> input_files) {
  std::ofstream output(input_files[0], std::ios_base::app);

  for (int file_count = 1; file_count < input_files.size(); file_count++) {
    std::ifstream file(input_files[file_count], std::ios::binary);

    size_t name_size = input_files[file_count].size();

    file.seekg(0, std::ios::end);
    int file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::bitset<8> null;

    int chunk_size = 16;
    int chunk_count = (file_size + 1) / 2;

    int header_size = name_size * 8 + 4 * 8;

    // Encode filename
    for (int i = 0; i < name_size; i++) {
      std::bitset<8> buffer(input_files[file_count][i]);
      encodeChunk(buffer, &output);
    }

    encodeChunk(null, &output);

    std::bitset<32> chunk_b(chunk_count);

    for (int i = 0; i < 4; i++) {
      std::bitset<8> buffer;
      for (int j = 0; j < 8; j++) {
        buffer[j] = chunk_b[i * 8 + j];
      }
      encodeChunk(buffer, &output);
    }

    encodeChunk(null, &output);

    std::bitset<8> buffer;

    int counter = 0;

    while (!file.eof()) {
      file.read((char *)&buffer, 1);

      if (file.eof()) break;

      encodeChunk(buffer, &output);

      if (counter % 5 == 0) {
        printProgress(counter / chunk_count, input_files[file_count]);
      }

      counter++;
    }

    encodeChunk(null, &output);

    std::cout << "\n";
  }
}

// Concats 2 or more archives
void Concat(std::vector<std::string> input_files) {
  std::ofstream output(input_files[0], std::ios_base::app);

  for (int i = 1; i < input_files.size(); i++) {
    std::ifstream input(input_files[i], std::ios::binary | std::ios::ate);

    std::cout << input.tellg() << "\n";

    input.seekg(0, std::ios::beg);

    while (!input.eof()) {
      std::bitset<16> buffer;
      buffer = readChunk(&input);

      writeChunk(buffer, &output);

      if (input.eof()) break;
    }
  }
}

// Deletes a file from archive
void Delete(std::vector<std::string> input_files) {
  std::bitset<8> null;

  std::ifstream file(input_files[0], std::ios::binary | std::ios::ate);

  std::string tmp_filename = "." + input_files[0] + ".swp";
  std::ofstream output(tmp_filename);

  std::bitset<block_size> chunk;
  std::bitset<8> buffer;

  file.seekg(0, std::ios::beg);

  while (!file.eof()) {
    std::string filename;

    std::cout << "Working with some file\n";

    chunk = readChunk(&file);
    if (!chunk.none()) {
      file.seekg(-2, std::ios::cur);
    }

    std::cout << file.tellg() << "\n";

    for (std::bitset<8> buffer(1); !buffer.none();) {
      chunk = readChunk(&file);
      buffer = decodeChunk(chunk);
      reverse(buffer);

      filename += (char)buffer.to_ulong();
    }

    std::cout << filename << " ";

    std::bitset<32> chunk_count;

    int i = 0;

    for (std::bitset<8> buffer(1); i < 4;) {
      chunk = readChunk(&file);
      buffer = decodeChunk(chunk);
      reverse(buffer);

      for (int j = 0; j < 8; j++) {
        chunk_count[i * 8 + j] = buffer[j];
      }
      i++;
    }

    std::cout << chunk_count.to_ulong() << "\n";

    if (std::strcmp(filename.c_str(), input_files[1].c_str()) == 0) {
      file.ignore((chunk_count.to_ulong() * 4) + 2);

      std::cout << "Deleted " << filename << "\n";
    } else {

      for (int i = 0; i < filename.size(); i++) {
        std::bitset<8> buffer(filename[i]);
        encodeChunk(buffer, &output);
      }

      for (int i = 0; i < 4; i++) {
        std::bitset<8> buffer;
        for (int j = 0; j < 8; j++) {
          buffer[j] = chunk_count[i * 8 + j];
        }
        encodeChunk(buffer, &output);
      }

      for (int i = 0; i < (chunk_count.to_ulong() * 2) + 1; i++) {

        writeChunk(readChunk(&file), &output);

      }

    }

    std::cout << "\n";

    if (file.eof()) break;
  }

  std::rename(tmp_filename.c_str(), input_files[0].c_str());
}