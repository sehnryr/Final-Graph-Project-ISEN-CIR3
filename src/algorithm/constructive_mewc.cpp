/**
 * @file constructive_mewc.cpp
 * @brief This file contains the implementation of the constructive MEWC algorithm
 * @authors
 * - Alexandre AUGUSTE <alexandre.auguste@isen-ouest.yncrea.fr>
 * - Martin LOBEL <martin.lobel@isen-ouest.yncrea.fr>
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-30
 */

#include <algorithm>

#include "mewc.hpp"
#include "../common.hpp"

/**
 * @brief Returns the vertex with the best criteria
 *
 * @param vertices The vertices to consider
 * @param sortedVertices The vertices sorted by a criteria
 * @return VertexPtr The vertex with the best criteria
 */
VertexPtr getBestVertex(
    std::unordered_set<VertexPtr> vertices,
    std::vector<VertexPtr> &sortedVertices) // O(n)
{
    VertexPtr bestVertex;

    for (std::vector<VertexPtr>::iterator it = sortedVertices.begin(); it != sortedVertices.end(); it++)
    {
        if (vertices.find(*it) != vertices.end())
        {
            bestVertex = *it;
            sortedVertices = std::vector<VertexPtr>(it, sortedVertices.end());
            break;
        }
    }

    return bestVertex;
}

/**
 * @brief Returns the vertices sorted by degree
 *
 * @param graph The graph
 * @param vertices The vertices to consider
 * @return std::vector<VertexPtr> The vertices sorted by degree
 */
std::vector<VertexPtr> sortVerticesDegree(
    Graph graph,
    std::unordered_set<VertexPtr> vertices) // O(nlogn)
{
    std::vector<std::pair<VertexPtr, long unsigned int>> degrees;
    std::vector<VertexPtr> sortedVertices;

    // Allocate the vectors
    degrees.reserve(vertices.size());
    sortedVertices.reserve(vertices.size());

    // Get the degrees
    auto adjMatrix = graph.getAdjacencyMatrix();
    for (auto vertex : vertices)
    {
        auto neighbors = adjMatrix[vertex->getId()];
        degrees.push_back(std::make_pair(vertex, neighbors.size()));
    }

    // Sort the vertices by degree
    std::sort(degrees.begin(), degrees.end(), [](const auto &a, const auto &b)
              { return a.second > b.second; });

    // Get the vertices
    for (const auto &[vertex, degree] : degrees)
        sortedVertices.push_back(vertex);

    return sortedVertices;
}

/**
 * @brief Returns the vertices sorted by the sum of their edges weights
 *
 * @param graph The graph
 * @param vertices The vertices to consider
 * @return std::vector<VertexPtr> The vertices sorted by the sum of their edges weights
 */
std::vector<VertexPtr> sortVerticesSumWeight(
    Graph graph,
    std::unordered_set<VertexPtr> vertices) // O(n^2)
{
    std::vector<std::pair<VertexPtr, long unsigned int>> weights;
    std::vector<VertexPtr> sortedVertices;

    // Allocate the vectors
    weights.reserve(vertices.size());
    sortedVertices.reserve(vertices.size());

    // Get the weights
    auto adjMatrix = graph.getAdjacencyMatrix();
    for (auto vertex : vertices)
    {
        long unsigned int weight = 0;
        auto neighbors = adjMatrix[vertex->getId()];
        for (const auto &[neighbor, edge] : neighbors)
        {
            weight += edge->getWeight();
        }
        weights.push_back(std::make_pair(vertex, weight));
    }

    // Sort the vertices by weight
    std::sort(weights.begin(), weights.end(), [](const auto &a, const auto &b)
              { return a.second > b.second; });

    // Get the vertices
    for (const auto &[vertex, weight] : weights)
        sortedVertices.push_back(vertex);

    return sortedVertices;
}

/**
 * @brief The recursive function of the constructive MEWC algorithm
 *
 * @param g The graph
 * @param clique The clique
 * @param P The set of vertices to consider
 */
void constructiveMEWCRecursive(
    Graph g,
    Clique &clique,
    std::unordered_set<VertexPtr> P,
    std::vector<VertexPtr> &sortedVertices)
{
    if (P.empty())
        return;

    VertexPtr newVertex = getBestVertex(P, sortedVertices);
    clique.addVertex(newVertex);

    std::unordered_set<VertexPtr> new_P;

    // Make the intersection of P and the neighbors of newVertex
    auto adjMatrix = g.getAdjacencyMatrix();
    for (const auto &[neighbor, _] : adjMatrix[newVertex->getId()])
        if (P.count(*(g.getVertex(neighbor))) != 0)
            new_P.insert(*(g.getVertex(neighbor)));

    constructiveMEWCRecursive(g, clique, new_P, sortedVertices);
}

/**
 * @brief Finds the maximum weight clique in a graph using a constructive
 * heuristic algorithm
 *
 * @param g The graph
 * @return Clique A guess of the maximum weight clique
 */
Clique constructiveMEWC(Graph g) // O(n^2)
{
    Clique clique;
    std::unordered_set<VertexPtr> P = g.getVertices();
    std::vector<VertexPtr> sortedVertices = sortVerticesDegree(g, P); // O(nlogn)
    // std::vector<VertexPtr> sortedVertices = sortVerticesSumWeight(g, P); // O(n^2)

    constructiveMEWCRecursive(g, clique, P, sortedVertices); // O(n^2)

    clique.setWeight(getCliqueWeight(g, clique).value()); // O(n^2)

    return clique;
}
