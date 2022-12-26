#include <sstream>

#include "common.hpp"

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