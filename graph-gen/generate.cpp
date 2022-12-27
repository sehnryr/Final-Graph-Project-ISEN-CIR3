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
    long unsigned int num_edges = max_edges / 100 * connectivity;

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Open the output file
    std::ofstream output_file(output_dir +
                              "/" + std::to_string(num_vertices) +
                              "_" + std::to_string(connectivity) +
                              ".in", std::ios::out);
    std::string line;

    // Check if the output file is open
    if (!output_file.is_open())
    {
        std::cout << "Error: Could not open output file" << std::endl;
        exit(1);
    }

    // Write the number of vertices and edges to the output file
    output_file << num_vertices << " " << num_edges << std::endl;

    // There cannot be edges that share the same vertices
    // so we need to keep track of which pairs of vertices have been used already
    // We can use a dictionary to do this
    std::map<std::pair<unsigned int, unsigned int>, bool> used_edges;

    // Generate the edges
    for (unsigned int i = 0; i < num_edges; i++)
    {
        // Generate a random pair of vertices where the first vertex is less than the second
        unsigned int v1 = rand() % num_vertices + 1;
        unsigned int v2 = rand() % num_vertices + 1;
        while (v1 == v2 || v1 > v2)
        {
            v1 = rand() % num_vertices + 1;
            v2 = rand() % num_vertices + 1;
        }

        // Check if the edge has already been used
        if (used_edges[std::make_pair(v1, v2)] == true)
        {
            // If it has, decrement the counter and try again
            i--;
            continue;
        }

        // Mark the edge as used
        used_edges[std::make_pair(v1, v2)] = true;

        unsigned short weight = rand() % 100 + 1;

        // Write the edge to the output file
        output_file << v1 << " " << v2 << " " << weight << std::endl;
    }

    return 0;
}

void print_usage(char **argv)
{
    std::cout << "Usage: " << argv[0] << " <num-vertices> <connectivity> [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --output-dir=<dir>   The directory to output the results to. Default: input directory" << std::endl;
    std::cout << "  --help               Print this message" << std::endl;
}