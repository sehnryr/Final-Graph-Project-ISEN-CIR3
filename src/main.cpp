#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

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
    std::string input_dir = input_path.substr(0, input_path.find_last_of("/"));
    std::string input_file = input_path.substr(input_dir.size() + 1);

    // Check if the input path is valid
    check_file(input_path);

    // Read the input file
    Graph graph = read_file(input_path);

    // Convert the arguments to a vector of strings excluding
    // the first and second arguments
    std::vector<std::string> args(argv + 2, argv + argc);

    // Find and pop the algorithm type argument
    std::string algorithm = "exact";
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        if ((*it).substr(0, 7) == "--type=")
        {
            algorithm = (*it).substr(7);
            args.erase(it);
            break;
        }
    }

    // Find and pop the --output= argument
    std::string output_dir = input_dir;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        if ((*it).substr(0, 13) == "--output-dir=")
        {
            output_dir = (*it).substr(13);
            args.erase(it);
            break;
        }
    }

    // Check if the output directory exists and is a directory
    if (!std::filesystem::exists(output_dir))
    {
        std::cout << "Output directory does not exist" << std::endl;
        exit(1);
    }
    if (!std::filesystem::is_directory(output_dir))
    {
        std::cout << "Output directory is not a directory" << std::endl;
        exit(1);
    }

    std::string output_file =
        input_file.substr(0, input_file.find_last_of(".")) + "_" + algorithm + ".out";
    // replace all '-' with '_' in the output file name
    std::replace(output_file.begin(), output_file.end(), '-', '_');

    // Check if there are any extra arguments
    if (args.size() > 0)
    {
        print_usage(argv);
        exit(1);
    }

    // Check if the algorithm type is valid
    if (algorithm == "exact")
    {
        // TODO: Implement exact algorithm
    }
    else if (algorithm == "constructive")
    {
        // TODO: Implement constructive heuristic algorithm
    }
    else if (algorithm == "local-search")
    {
        // TODO: Implement local search heuristic algorithm
    }
    else if (algorithm == "grasp")
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
              << " <input-file-path>"
              << " [--output-dir=<output-directory> --type=<algorithm-type>]"
              << std::endl;
}