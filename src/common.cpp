#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "common.hpp"

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

    // Create a vector of vertices of size num_vertices and initialize them
    std::vector<std::unique_ptr<Vertex>> vertices_unique(num_vertices);
    for (unsigned int i = 0; i < num_vertices; i++)
        vertices_unique[i] = std::make_unique<Vertex>(i + 1);
    std::vector<std::unique_ptr<Edge>> edges_unique;

    // Read the rest of the file
    while (std::getline(input_file, line))
    {
        // Check if the line has only numbers and spaces
        if (line.find_first_not_of("0123456789 ") != std::string::npos)
        {
            std::cout << "I1nput file has an invalid edge" << std::endl;
            exit(1);
        }

        // Split the line by the space char into the source and destination
        // vertices and the weight
        std::vector<std::string> splitted = split(line, ' ');

        // Check if the line has the correct number of elements
        if (splitted.size() != 3)
        {
            std::cout << "I2nput file has an invalid edge" << std::endl;
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
        std::unique_ptr<Vertex> &source_vertex = vertices_unique[source - 1];
        std::unique_ptr<Vertex> &destination_vertex = vertices_unique[destination - 1];

        // Create the edge
        Edge *edge = new Edge(source_vertex.get(), destination_vertex.get(), weight);
        edges_unique.push_back(std::unique_ptr<Edge>(edge));

        // Add the edge to the source and destination vertices
        source_vertex->addEdge(edge);
        destination_vertex->addEdge(edge);
    }

    // Close the input file
    input_file.close();

    // Check if the number of edges is correct
    if (edges_unique.size() != num_edges)
    {
        std::cout << "Input file has an invalid number of edges" << std::endl;
        exit(1);
    }

    // Convert the vectors of unique pointers to vectors of raw pointers
    std::vector<Vertex *> vertices;
    for (auto &vertex : vertices_unique)
        vertices.push_back(vertex.get());
    std::vector<Edge *> edges;
    for (auto &edge : edges_unique)
        edges.push_back(edge.get());

    // Create the graph
    return Graph(vertices, edges);
}

// Split a string by a delimiter into a vector of strings
// (from https://stackoverflow.com/a/236803)
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