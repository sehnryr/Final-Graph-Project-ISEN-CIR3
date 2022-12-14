/**
 * @file common.hpp
 * @brief Declaration of the common functions
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-26
 */

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
std::optional<long unsigned int> find_option(std::vector<std::string> args, std::string option);

#endif // COMMON_HPP