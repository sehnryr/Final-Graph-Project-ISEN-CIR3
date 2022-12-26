#include <iostream>
#include <string>

#include "common.hpp"

void print_usage(char **argv);

int main(int argc, char **argv)
{
    // Guard against no arguments
    if (argc < 2)
    {
        print_usage(argv);
        exit(1);
    }

    std::string input_path = argv[1];

    // Check if the input path is valid
    check_file(input_path);

    // Read the input file
    Graph graph = read_file(input_path);

    // Get the type of algorithm to use
    std::string algorithm = "exact";
    if (argc == 3)
    {
        // Check if the argument is valid
        // starts with --type=
        if (std::string(argv[2]).substr(0, 7) != "--type=")
        {
            print_usage(argv);
            exit(1);
        }

        // Get the algorithm type
        algorithm = std::string(argv[2]).substr(7);
    }

    // Check if the algorithm type is valid
    if (algorithm == "exact")
    {
        // TODO: Implement exact algorithm
    }
    else if (algorithm == "constructive-heuristic")
    {
        // TODO: Implement constructive heuristic algorithm
    }
    else if (algorithm == "local-search-heuristic")
    {
        // TODO: Implement local search heuristic algorithm
    }
    else if (algorithm == "grasp-meta-heuristic")
    {
        // TODO: Implement grasp meta heuristic algorithm
    }
    else
    {
        print_usage(argv);
        exit(1);
    }

    return 0;
}

void print_usage(char **argv)
{
    std::cout << "Usage: "
              << argv[0]
              << " <input-file-path> [--type=<algorithm-type>]"
              << std::endl;
}