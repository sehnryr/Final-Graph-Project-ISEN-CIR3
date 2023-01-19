/**
 * @file mewc.hpp
 * @brief This file contains the interface of the MEWC algorithm
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-27
 */

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

Clique exactMEWC(const Graph &g);
Clique constructiveMEWC(const Graph &g);
Clique localSearchMEWC(const Graph &g);
Clique graspMEWC(const Graph &g);
Clique runMEWC(const Graph &graph, const Algorithm &algorithm);

Algorithm getAlgorithm(const std::string &algorithm);
std::string getAlgorithmName(const Algorithm &algorithm);

#endif // MEWC_HPP