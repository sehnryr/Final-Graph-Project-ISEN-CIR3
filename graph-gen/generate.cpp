#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

void print_usage(char **argv);

int main(int argc, char **argv)
{
    // Guard against no arguments
    if (argc < 3)
    {
        print_usage(argv);
        exit(1);
    }

    std::vector<std::string> args(argv + 3, argv + argc);

    for (auto it = args.begin(); it != args.end(); ++it)
    {
        if (*it == "--help")
        {
            print_usage(argv);
            exit(0);
        }
    }

    // Find and pop the --output= argument
    std::string output_dir = "";
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        if ((*it).substr(0, 13) == "--output-dir=")
        {
            output_dir = (*it).substr(13);
            args.erase(it);
            break;
        }
    }

    // Check if there are any extra arguments
    if (args.size() > 0)
    {
        print_usage(argv);
        exit(1);
    }

    // Check if the number of vertices and connectivity are valid integers
    if (std::string(argv[1]).find_first_not_of("0123456789") != std::string::npos ||
        std::stoi(argv[1]) < 0)
    {
        std::cout << "Error: Invalid number of vertices" << std::endl;
        exit(1);
    }
    if (std::string(argv[2]).find_first_not_of("0123456789") != std::string::npos ||
        std::stoi(argv[2]) < 0 ||
        std::stoi(argv[2]) > 100)
    {
        std::cout << "Error: Invalid connectivity" << std::endl;
        exit(1);
    }

    unsigned int num_vertices = std::stoi(argv[1]);
    unsigned int connectivity = std::stoi(argv[2]);

    long unsigned int max_edges = num_vertices * (num_vertices - 1) / 2;
    long unsigned int num_edges = (max_edges * connectivity + 50) / 100;
    // We add 50 to round the fraction to the nearest integer

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Open the output file
    std::ofstream output_file(output_dir +
                                  "/" + std::to_string(num_vertices) +
                                  "_" + std::to_string(connectivity) +
                                  ".in",
                              std::ios::out);

    // Check if the output file is open
    if (!output_file.is_open())
    {
        std::cout << "Error: Could not open output file" << std::endl;
        exit(1);
    }

    // Write the number of vertices and edges to the output file
    output_file << num_vertices << " " << num_edges << std::endl;

    for (unsigned int i = 0; i < num_vertices; i++)
        for (unsigned int j = i + 1; j < num_vertices; j++)
        {
            if (rand() % max_edges < num_edges)
            {
                unsigned int weight = rand() % 100 + 1;
                output_file << i + 1 << " " << j + 1 << " " << weight << std::endl;
                num_edges--;
            }
            max_edges--;
        }
    
    // Close the output file
    output_file.close();

    return 0;
}

void print_usage(char **argv)
{
    std::cout << "Usage: " << argv[0] << " <num-vertices> <connectivity> [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --output-dir=<dir>   The directory to output the results to. Default: input directory" << std::endl;
    std::cout << "  --help               Print this message" << std::endl;
}