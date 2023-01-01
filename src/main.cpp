/**
 * @file main.cpp
 * @brief Implementation of the main function
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-12
 */

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "common.hpp"
#include "algorithm/mewc.hpp"

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
    if (argc < 2)
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

    // Find and pop the algorithm type argument
    Algorithm algorithm = Algorithm::Exact;
    if (auto i = find_option(args, "--type="))
    {
        try
        {
            std::string algorithm_name = args.at(i.value()).substr(7);
            algorithm = getAlgorithm(algorithm_name);
        }
        catch (const std::invalid_argument &e)
        {
            print_usage(argv);
            exit(1);
        }
        args.erase(args.begin() + i.value());
    }

    // Find and pop the output-dir argument
    std::string output_dir = "//unset";
    if (auto i = find_option(args, "--output-dir="))
    {
        output_dir = args.at(i.value()).substr(13);
        args.erase(args.begin() + i.value());
    }

    // Find and pop the runs argument
    int runs = 1;
    if (auto i = find_option(args, "--runs="))
    {
        runs = std::stoi(args.at(i.value()).substr(7));
        args.erase(args.begin() + i.value());
    }

    // Check if the input-file argument is set
    if (args.size() != 1)
    {
        print_usage(argv);
        exit(1);
    }

    std::string input_path = args[0];
    // Check if the input path is valid
    check_file(input_path);

    std::string input_dir = input_path.substr(0, input_path.find_last_of("/"));
    std::string input_file = input_path.substr(input_dir.size() + 1);

    // Check if the value of output_dir is unset
    if (output_dir == "//unset")
        output_dir = input_dir;

    // Check if the output directory is valid
    check_directory(output_dir);

    std::string output_file =
        input_file.substr(0, input_file.find_last_of(".")) +
        "_" + getAlgorithmName(algorithm) + ".out";
    // replace all '-' with '_' in the output file name
    std::replace(output_file.begin(), output_file.end(), '-', '_');

    // Read the input file
    Graph graph = read_file(input_path);
    Clique clique;

    // Run the algorithm
    for (int i = 0; i < runs; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        clique = runMEWC(graph, algorithm);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << std::endl;
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
    std::cout << "Usage: " << argv[0] << " <input-file> [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --type=<type>        The algorithm type to use. Default: exact" << std::endl;
    std::cout << "  --output-dir=<dir>   The directory to output the results to. Default: input directory" << std::endl;
    std::cout << "  --runs=<n>           The number of times to run the algorithm. Default: 1" << std::endl;
    std::cout << "  --help               Print this message" << std::endl;
}