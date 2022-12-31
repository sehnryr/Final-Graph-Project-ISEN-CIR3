#include <optional>
#include <string>
#include <vector>

#include "model/graph.hpp"

#ifndef COMMON_HPP
#define COMMON_HPP

// Macro to suppress unused variable warnings
#define UNUSED(x) (void)(x)

void check_file(std::string path);
void check_directory(std::string path);
Graph read_file(std::string path);
std::vector<std::string> split(const std::string &s, char delim);
std::optional<std::vector<std::string>::iterator> find_option(std::vector<std::string> args, std::string option);


#endif // COMMON_HPP