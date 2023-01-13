/**
 * @file constructive_mewc.cpp
 * @brief This file contains the implementation of the constructive MEWC algorithm
 * @authors
 * - Alexandre AUGUSTE <alexandre.auguste@isen-ouest.yncrea.fr>
 * - Martin LOBEL <martin.lobel@isen-ouest.yncrea.fr>
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-30
 */

#include "mewc.hpp"
#include "../common.hpp"

/**
 * @brief Returns the vertex with the highest degree
 *
 * @param graph The graph
 * @param vertices The vertices to consider
 * @return VertexPtr The vertex with the highest degree
 */
VertexPtr getVertexHighestDegree(Graph graph, std::unordered_set<VertexPtr> vertices) // O(n)
{
    VertexPtr bestVertex;
    long unsigned int bestDegree = 0;
    auto adjMatrix = graph.getAdjacencyMatrix();

    for (auto vertex : vertices)
    {
        auto neighbors = adjMatrix[vertex->getId()];
        if (neighbors.size() > bestDegree)
        {
            bestDegree = neighbors.size();
            bestVertex = vertex;
        }
    }

    return bestVertex;
}

/**
 * @brief Returns the vertex with the highest commulative weight of its edges
 *
 * @param graph The graph
 * @param vertices The vertices to consider
 * @return VertexPtr The vertex with the highest commulative weight of its edges
 */
VertexPtr getVertexHighestSumWeight(Graph graph, std::unordered_set<VertexPtr> vertices) // O(n^2)
{
    VertexPtr bestVertex;
    long unsigned int bestWeight = 0;
    auto adjMatrix = graph.getAdjacencyMatrix();

    for (auto vertex : vertices)
    {
        long unsigned int weight = 0;
        auto neighbors = adjMatrix[vertex->getId()];
        for (const auto &[neighbor, edge] : neighbors)
        {
            weight += edge->getWeight();
        }
        if (weight > bestWeight)
        {
            bestWeight = weight;
            bestVertex = vertex;
        }
    }

    return bestVertex;
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
    std::unordered_set<VertexPtr> P)
{
    if (P.empty())
        return;

    VertexPtr newVertex = getVertexHighestDegree(g, P);
    clique.addVertex(newVertex);

    std::unordered_set<VertexPtr> new_P;

    // Make the intersection of P and the neighbors of newVertex
    auto adjMatrix = g.getAdjacencyMatrix();
    for (const auto &[neighbor, _] : adjMatrix[newVertex->getId()])
        if (P.count(*(g.getVertex(neighbor))) != 0)
            new_P.insert(*(g.getVertex(neighbor)));

    constructiveMEWCRecursive(g, clique, new_P);
}

/**
 * @brief Finds the maximum weight clique in a graph using a constructive
 * heuristic algorithm
 *
 * @param g The graph
 * @return Clique A guess of the maximum weight clique
 */
Clique constructiveMEWC(Graph g)
{
    Clique clique;
    std::unordered_set<VertexPtr> P = g.getVertices();

    constructiveMEWCRecursive(g, clique, P);

    clique.setWeight(getCliqueWeight(g, clique).value());

    return clique;
}
