#include "number.h"

#include <cmath>

uint2022_t from_uint(uint32_t i, int shift = 0) {
  // somehow get from_uint to array arrangement

  uint2022_t result;

  for (int i = 0; i < kSize; i++) {
    result.data[i] = 0;
  }

  result.data[kSize - 1 - shift] = (i % kBase);
  result.data[kSize - 2 - shift] = (i / kBase);

  return result;
}

uint2022_t from_string(const char* buff) {
  // convert a char buffer to ints and into array

  uint2022_t result;

  std::string line = buff;

  while (line.size() < kSize * 9) {
    line = '0' + line;
  }

  for (int i = 0; i < kSize * 9; i += 9) {
    std::uint32_t sum = 0;

    for (int counter = 0, c = kBase / 10; counter < 9; counter++, c /= 10) {
      sum += int(line[i + counter] - '0') * c;
    }

    result.data[i / 9] = sum;
  }

  return result;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
  uint2022_t result;

  std::uint32_t sum = 0;

  std::uint32_t overflow = 0;

  for (int i = kSize - 1; i >= 0; i--) {
    sum = lhs.data[i] + rhs.data[i] + overflow;
    result.data[i] = sum % kBase;
    overflow = sum / kBase;
  }

  return result;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
  uint2022_t result;

  std::uint32_t carry = 0;

  for (int i = kSize - 1; i > 0; i--) {
    if (lhs.data[i] < rhs.data[i]) {
      result.data[i] = lhs.data[i] + kBase - rhs.data[i] - carry;
      carry = 1;
    } else {
      result.data[i] = lhs.data[i] - rhs.data[i] - carry;
      carry = 0;
    }
  }

  return result;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
  // You have 3h to implement this

  uint2022_t result;
  uint2022_t tmp;

  result = from_uint(0);

  for (int i = kSize - 1, c = 0; i > 0; i--, c++) {
    for (int j = kSize - 1, k = 0; j > 0; j--, k++) {
      tmp = from_uint(rhs.data[i] * lhs.data[j], c + k);

      result = result + tmp;
    }
  }

  return result;
}

// uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
// }

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
  for (int i = 0; i < kSize; i++) {
    if (lhs.data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
  return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
  int i = 0;

  while (value.data[i] == 0 && i < kSize - 1) {
    i++;
  }

  int flag = i;

  while (i < kSize) {
    if (i == flag) {
      stream << value.data[i] % kBase;
    } else {
      stream.width(9);
      stream.fill('0');
      stream << value.data[i] % kBase;
    }
    i++;
  }

  return stream;
}
