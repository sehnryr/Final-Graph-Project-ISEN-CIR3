/**
 * @file generate.cpp
 * @brief This file contains the main function of the graph generator
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-27
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <random>

/**
 * @brief Find an option in the arguments
 *
 * This method finds an option in the arguments and returns its index.
 *
 * @param args The arguments
 * @param option The option
 * @return std::optional<long unsigned int> The index of the option or an empty optional
 */
std::optional<long unsigned int> find_option(std::vector<std::string> args, std::string option)
{
    for (auto it = args.begin(); it != args.end(); ++it)
        if (it->substr(0, option.size()) == option)
            return it - args.begin();
    return {};
}

void print_usage(char **argv);

/**
 * @brief Main function
 *
 * This method is the main function of the program. It parses the command line arguments
 * and runs the algorithm.
 *
 * @param argc The number of command line arguments
 * @param argv The command line arguments
 * @return int The exit code
 */
int main(int argc, char **argv)
{
    // Guard against no arguments
    if (argc < 3)
    {
        print_usage(argv);
        exit(1);
    }

    std::vector<std::string> args(argv + 1, argv + argc);

    // Find the --help argument
    if (find_option(args, "--help"))
    {
        print_usage(argv);
        exit(0);
    }

    // Find and pop the output-dir argument
    std::string output_dir = ".";
    if (auto i = find_option(args, "--output-dir="))
    {
        output_dir = args.at(i.value()).substr(13);
        args.erase(args.begin() + i.value());
    }

    // Check if the num-vertices and connectivity arguments are set
    if (args.size() != 2)
    {
        print_usage(argv);
        exit(1);
    }

    // Check if the number of vertices and connectivity are valid integers
    if (args[0].find_first_not_of("0123456789") != std::string::npos ||
        std::stoi(args[0]) < 0)
    {
        std::cout << "Error: Invalid number of vertices" << std::endl;
        exit(1);
    }
    if (args[1].find_first_not_of("0123456789") != std::string::npos ||
        std::stoi(args[1]) < 0 ||
        std::stoi(args[1]) > 100)
    {
        std::cout << "Error: Invalid connectivity" << std::endl;
        exit(1);
    }

    std::string output_path = output_dir + "/" + args[0] + "_" + args[1] + ".in";

    unsigned int num_vertices = std::stoi(args[0]);
    unsigned int connectivity = std::stoi(args[1]);

    long unsigned int max_edges = num_vertices * (num_vertices - 1) / 2;
    long unsigned int num_edges = (max_edges * connectivity + 50) / 100;
    // We add 50 to round the fraction to the nearest integer

    // Seed the random number generator with the current time
    std::random_device rd;
    std::mt19937 gen(rd());

    // Open the output file
    std::ofstream output_file(output_path, std::ios::out);

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
            if ((long unsigned int)(std::uniform_int_distribution<>(0, max_edges - 1)(gen)) < num_edges)
            {
                unsigned int weight = std::uniform_int_distribution<>(1, 100)(gen);
                output_file << i + 1 << " " << j + 1 << " " << weight << std::endl;
                num_edges--;
            }
            max_edges--;
        }

    // Close the output file
    output_file.close();

    return 0;
}

/**
 * @brief Print the usage message
 *
 * This function prints the usage message to the console. It is called when the
 * program is run with no arguments or with the --help argument or when the
 * the arguments are invalid.
 *
 * @param argv The command line arguments
 */
void print_usage(char **argv)
{
    std::cout << "Usage: " << argv[0] << " <num-vertices> <connectivity> [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --output-dir=<dir>   The directory to output the results to. Default: input directory" << std::endl;
    std::cout << "  --help               Print this message" << std::endl;
}