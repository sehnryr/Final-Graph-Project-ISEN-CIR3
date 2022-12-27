#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "common.hpp"
#include "algorithm/mewc.hpp"

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

    // Convert the arguments to a vector of strings excluding
    // the first and second arguments
    std::vector<std::string> args(argv + 2, argv + argc);

    // Find and pop the --help argument
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        if (*it == "--help")
        {
            print_usage(argv);
            exit(0);
        }
    }

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

    // Check if the input path is valid
    check_file(input_path);

    // Read the input file
    Graph graph = read_file(input_path);
    Clique clique;

    // Check if the algorithm type is valid
    if (algorithm == "exact")
    {
        clique = exactMEWC(graph);
    }
    else if (algorithm == "constructive")
    {
        clique = constructiveMEWC(graph);
    }
    else if (algorithm == "local-search")
    {
        clique = localSearchMEWC(graph);
    }
    else if (algorithm == "grasp")
    {
        clique = graspMEWC(graph);
    }
    else
    {
        print_usage(argv);
        exit(1);
    }

    // Write the output file
    std::ofstream output(output_dir + "/" + output_file, std::ios::out);

    // Check if the output file is open
    if (!output.is_open())
    {
        std::cout << "Error: Could not open output file" << std::endl;
        exit(1);
    }

    // Write the size of the clique and the weight of the clique
    output << clique.getVertices().size() << " "
                << clique.getWeight() << std::endl;

    // Write the vertices of the clique
    for (auto vertex : clique.getVertices())
        output << vertex->getId() << " ";
    output << std::endl;

    // Close the output file
    output.close();

    return 0;
}

void print_usage(char **argv)
{
    std::cout << "Usage: " << argv[0] << " <input-file> [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --type=<type>        The algorithm type to use. Default: exact" << std::endl;
    std::cout << "  --output-dir=<dir>   The directory to output the results to. Default: input directory" << std::endl;
    std::cout << "  --help               Print this message" << std::endl;
}