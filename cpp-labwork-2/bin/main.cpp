
#include <lib/number.h>
#include <iostream>

int main() {
    uint2022_t value1;
    uint2022_t value2;

    // value1 = from_string("6");
    value1 = from_string("5000000000");
    value2 = from_string("1000000000");

    std::cout << value1 * value2 << std::endl;

    return 0;
} 
