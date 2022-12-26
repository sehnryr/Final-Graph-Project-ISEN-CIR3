#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "common.hpp"

int main(int argc, char **argv)
{
    // Guard against no arguments
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <input-file-path>" << std::endl;
        return 1;
    }

    std::string input_path = argv[1];

    // Check if the input path is valid
    check_file(input_path);

    // Read the input file
    Graph graph = read_file(input_path);

    return 0;
}