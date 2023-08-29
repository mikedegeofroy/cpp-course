#include <functional>
#include <lib/ArgParser.h>

#include <iostream>
#include <numeric>

#include <sstream>

struct Options {
    bool sum = false;
    bool mult = false;
};


int main(int argc, char** argv) {
    Options opt;

    ArgumentParser::ArgParser parser("Program");

    std::vector<int> values;


    parser.AddFlag("sum", "add args").StoreValue(opt.sum).Default(false);
    parser.AddFlag("mult", "multiply args").StoreValue(opt.mult).Default(false);
    parser.AddIntArgument("N").MultiValue(2).Positional().StoreValues(values);

    if(!parser.Parse(argc, argv)) {
        std::cout << "Wrong argument" << std::endl;
        return 1;
    }

    if(opt.sum) {
        std::cout << "Result: " << std::accumulate(values.begin(), values.end(), 0) << std::endl;
    } else if(opt.mult) {
        std::cout << "Result: " << std::accumulate(values.begin(), values.end(), 1, std::multiplies<int>()) << std::endl;
    } else {
        std::cout << "No one options had chosen" << std::endl;
        return 1;
    }

    return 0;

}
