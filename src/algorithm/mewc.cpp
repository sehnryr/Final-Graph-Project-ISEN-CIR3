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