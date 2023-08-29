#include <iostream>

#include <lib/parser.h>

using namespace omfl;

int main(int, char**) {

    // const auto root = parse(data);
    auto root = parseFile("test.omfl");

    std::cout << root.Get("apricot.size").AsInt() << "\n";

    return 0;
}
