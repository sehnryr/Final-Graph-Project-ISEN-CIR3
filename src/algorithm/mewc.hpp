#include <string>

#include "../model/clique.hpp"
#include "../model/graph.hpp"

#ifndef MEWC_HPP
#define MEWC_HPP

enum Algorithm
{
    Exact,
    Constructive,
    LocalSearch,
    Grasp
};

Clique exactMEWC(Graph g);
Clique constructiveMEWC(Graph g);
Clique localSearchMEWC(Graph g);
Clique graspMEWC(Graph g);
Clique runMEWC(Graph graph, Algorithm algorithm);

Algorithm getAlgorithm(std::string algorithm);
std::string getAlgorithmName(Algorithm algorithm);

#endif // MEWC_HPP