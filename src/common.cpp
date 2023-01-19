/**
 * @file common.cpp
 * @brief Implementation of the common functions
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-26
 */

#include <filesystem>
#include <fstream>
#include <iostream>

#include "common.hpp"

/**
 * @brief Check if the input file is valid
 *
 * This method checks if the input file is valid. If it is not, it exits the program.
 * The validity of the input file is checked by checking if the path exists,
 * if the path is a file and if the path is in the correct format.
 *
 * @param path The path to the input file
 */
void check_file(std::string path)
{
    // Check if the input path exists
    if (!std::filesystem::exists(path))
    {
        std::cout << "Input path does not exist" << std::endl;
        exit(1);
    }

    // Check if the input path is a file
    if (!std::filesystem::is_regular_file(path))
    {
        std::cout << "Input path is not a file" << std::endl;
        exit(1);
    }

    // Check if the input path is in the correct format
    if (path.substr(path.find_last_of(".") + 1) != "in")
    {
        std::cout << "Input path is not a .in file" << std::endl;
        exit(1);
    }
}

/**
 * @brief Check if the output directory is valid
 *
 * This method checks if the output directory is valid. If it is not, it exits the program.
 * The validity of the output directory is checked by checking if the path exists
 * and if the path is a directory.
 */
void check_directory(std::string path)
{
    // Check if the path exists
    if (!std::filesystem::exists(path))
    {
        std::cout << "Path does not exist : " << path << std::endl;
        exit(1);
    }

    // Check if the path is a directory
    if (!std::filesystem::is_directory(path))
    {
        std::cout << "Path is not a directory : " << path << std::endl;
        exit(1);
    }
}

/**
 * @brief Read the input file and return a graph
 *
 * This method reads the input file and returns a graph.
 * The input file must be composed of the number of vertices and edges on the first line,
 * followed by the edges on the next lines. The edges must be composed of three numbers
 * separated by a space char. The first number is the id of the first vertex, the second
 * number is the id of the second vertex and the third number is the weight of the edge.
 *
 * @param path The path to the input file
 * @return Graph The graph
 */
Graph read_file(std::string path)
{
    // Read the input file
    std::ifstream input_file(path, std::ios::in);
    std::string line;

    // Check if the input file is open
    if (!input_file.is_open())
    {
        std::cout << "Input file could not be opened" << std::endl;
        exit(1);
    }

    // Read the first line
    std::getline(input_file, line);

    // Split the first line by the space char into
    // the number of vertices and edges
    std::vector<std::string> first_line = split(line, ' ');

    // Check if the line has only numbers and spaces
    if (line.find_first_not_of("0123456789 ") != std::string::npos)
    {
        std::cout << "Input file has an invalid first line" << std::endl;
        exit(1);
    }

    // Check if the first line has the correct number of elements
    if (first_line.size() != 2)
    {
        std::cout << "Input file has an invalid first line" << std::endl;
        exit(1);
    }

    // Convert the number of vertices and edges to integers
    unsigned int num_vertices = std::stoi(first_line[0]);
    long unsigned int num_edges = std::stoi(first_line[1]);

    Graph graph = Graph();

    // Create a vector of vertices of size num_vertices and initialize them
    std::vector<VertexPtr> vertices(num_vertices);
    for (unsigned int i = 0; i < num_vertices; i++)
    {
        vertices[i] = std::make_shared<Vertex>(i + 1);
        graph.addVertex(vertices[i]);
    }

    // Read the rest of the file
    while (std::getline(input_file, line))
    {
        // Check if the line has only numbers and spaces
        if (line.find_first_not_of("0123456789 ") != std::string::npos)
        {
            std::cout << "Input file has an invalid edge" << std::endl;
            exit(1);
        }

        // Split the line by the space char into the source and destination
        // vertices and the weight
        std::vector<std::string> splitted = split(line, ' ');

        // Check if the line has the correct number of elements
        if (splitted.size() != 3)
        {
            std::cout << "Input file has an invalid edge" << std::endl;
            exit(1);
        }

        // Convert the source and destination vertices to integers
        unsigned int source = std::stoi(splitted[0]);
        unsigned int destination = std::stoi(splitted[1]);
        unsigned int weight = std::stoi(splitted[2]);

        // Check if the source and destination vertices are valid
        if (source < 1 ||
            source > num_vertices ||
            destination < 1 ||
            destination > num_vertices)
        {
            std::cout << "Input file has an invalid edge" << std::endl;
            exit(1);
        }

        // Get the source and destination vertices
        VertexPtr source_vertex = vertices[source - 1];
        VertexPtr destination_vertex = vertices[destination - 1];

        // Create the edge
        EdgePtr edge = std::make_shared<Edge>(source_vertex, destination_vertex, weight);
        graph.addEdge(edge);
    }

    // Close the input file
    input_file.close();

    // Check if the number of edges is correct
    if (graph.edges().size() != num_edges)
    {
        std::cout << "Input file has an invalid number of edges" << std::endl;
        exit(1);
    }

    // Create the graph
    return graph;
}

/**
 * @brief Split a string by a delimiter
 *
 * This method splits a string by a delimiter and returns a vector of strings.
 * (from https://stackoverflow.com/a/236803)
 *
 * @param s The string to split
 * @param delim The delimiter
 * @return std::vector<std::string> The vector of strings
 */
std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

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