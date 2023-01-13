/**
 * @file mewc.cpp
 * @brief This file contains the implementation of generic MEWC functions
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-30
 */

#include <iostream>

#include "mewc.hpp"

/**
 * @brief Run the algorithm
 *
 * This function runs the algorithm specified by the algorithm argument. It is
 * called by the main function.
 *
 * @param graph The graph to run the algorithm on
 * @param algorithm The algorithm to run
 * @param argv The command line arguments
 * @return Clique The clique found by the algorithm
 * @throws std::invalid_argument If the algorithm is invalid
 */
Clique runMEWC(Graph graph, Algorithm algorithm)
{
    switch (algorithm)
    {
    case Algorithm::Exact:
        return exactMEWC(graph);
    case Algorithm::Constructive:
        return constructiveMEWC(graph);
    case Algorithm::LocalSearch:
        return localSearchMEWC(graph);
    case Algorithm::Grasp:
        return graspMEWC(graph);
    default:
        throw std::invalid_argument("Invalid algorithm");
    }
}

/**
 * @brief Get the algorithm from a string
 *
 * This function returns the algorithm corresponding to the string passed as
 * argument. It is called by the main function.
 *
 * @param algorithm The string to convert
 * @return Algorithm The algorithm corresponding to the string
 * @throws std::invalid_argument If the string is invalid
 */
Algorithm getAlgorithm(std::string algorithm)
{
    if (algorithm == "exact")
        return Algorithm::Exact;
    else if (algorithm == "constructive")
        return Algorithm::Constructive;
    else if (algorithm == "local-search")
        return Algorithm::LocalSearch;
    else if (algorithm == "grasp")
        return Algorithm::Grasp;
    else
        throw std::invalid_argument("Invalid algorithm");
}

/**
 * @brief Get the name of the algorithm
 *
 * This function returns the name of the algorithm passed as argument. It is
 * called by the main function.
 *
 * @param algorithm The algorithm to get the name of
 * @return std::string The name of the algorithm
 */
std::string getAlgorithmName(Algorithm algorithm)
{
    switch (algorithm)
    {
    case Algorithm::Exact:
        return "exact";
    case Algorithm::Constructive:
        return "constructive";
    case Algorithm::LocalSearch:
        return "local-search";
    case Algorithm::Grasp:
        return "grasp";
    default:
        return "invalid";
    }
}

/**
 * @brief Get the weight of a clique
 *
 * This function calculates the weight of a clique. If the clique is not a clique,
 * it returns an empty optional.
 *
 * The time complexity of this function is O(n^2), where n is the size of the clique.
 *
 * @param clique The clique to get the weight of
 * @return std::optional<long unsigned int> The weight of the clique, an empty optional
 * if the clique is not a clique
 */
std::optional<long unsigned int> getCliqueWeight(Graph graph, Clique clique)
{
    // variable to store the weight of the clique
    long unsigned int weight = 0;
    // get a set of all vertices in the clique
    std::unordered_set<VertexPtr> vertices = clique.getVertices();

    // iterate over all possible pairs of vertices in the clique
    for (auto v1 : vertices)
        for (auto v2 : vertices)
            // if the vertices are the same, continue
            if (v1 == v2)
                continue;
            // if the vertices are connected, add the weight of the edge
            // to the weight of the clique
            else if (auto edge = graph.getEdge(v1, v2))
                weight += edge.value()->getWeight();
            // if the vertices are not connected, the clique is not a clique
            else
                return {};

    // return the weight of the clique divided by 2 because each edge is counted twice
    return weight / 2;
}