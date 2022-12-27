#include <string>
#include <vector>

#include "model/graph.hpp"

#ifndef COMMON_HPP
#define COMMON_HPP

#define UNUSED(x) (void)(x)

// Check if a file exists and is a file and is a .in file
void check_file(std::string path);
// Read a file and return a graph
Graph read_file(std::string path);
// Split a string by a delimiter into a vector of strings
std::vector<std::string> split(const std::string &s, char delim);

#endif // COMMON_HPP