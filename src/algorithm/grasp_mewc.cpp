/**
 * @file grasp_mewc.cpp
 * @brief This file contains the implementation of the grasp MEWC algorithm
 * @authors
 * - Antoine ESNAULT <antoine.esnault@isen-ouest.yncrea.fr>
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-30
 */

#include <random>

#include "mewc.hpp"
#include "../common.hpp"

#define ALPHA 0.5  // restricted candidate list parameter
#define RETRIES 10 // number of retries for the grasp algorithm

/**
 * @brief Returns the sum of the adjacent edges of a vertex
 *
 * @param graph The graph
 * @param vertex The vertex to consider
 * @return long unsigned int The sum of the adjacent edges of a vertex
 */
long unsigned int getSumAdjacentEdges(
    Graph graph,
    VertexPtr vertex) // O(n)
{
    long unsigned int sum = 0;
    auto adjMatrix = graph.getAdjacencyMatrix();
    auto neighbors = adjMatrix[vertex->getId()];
    for (const auto &[neighbor, edge] : neighbors)
        sum += edge->getWeight();
    return sum;
}

/**
 * @brief Returns the maximum sum of the adjacent edges of a vertex
 *
 * @param graph The graph
 * @param vertices The vertices to consider
 * @return long unsigned int The maximum sum of the adjacent edges of a vertex
 */
long unsigned int getGamma(
    Graph graph,
    std::unordered_set<VertexPtr> vertices) // O(n^2)
{
    long unsigned int gamma = 0;
    auto adjMatrix = graph.getAdjacencyMatrix();
    for (auto vertex : vertices)
    {
        long unsigned int weight = getSumAdjacentEdges(graph, vertex);
        if (weight > gamma)
            gamma = weight;
    }
    return gamma;
}

/**
 * @brief Create the Restricted Candidate List
 *
 * @param graph The graph
 * @param vertices The vertices to consider
 * @return std::vector<VertexPtr> The Restricted Candidate List
 */
std::vector<VertexPtr> MakeRCL(
    Graph graph,
    std::unordered_set<VertexPtr> vertices) // O(n^2)
{
    long unsigned int gamma = getGamma(graph, vertices);
    std::vector<VertexPtr> RCL;
    for (auto vertex : vertices)
    {
        long unsigned int weight = getSumAdjacentEdges(graph, vertex);
        if (weight < gamma / (1 + ALPHA))
            RCL.push_back(vertex);
    }
    return RCL;
}

/**
 * @brief Select a vertex inside the Restricted Candidate List randomly
 *
 * @param std::vector<VertexPtr> RCL
 * @return std::vector<VertexPtr> The vertex choose randomly
 */
VertexPtr SelectElementAtRandom(std::vector<VertexPtr> &RCL) // O(1)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, RCL.size() - 1);
    return RCL[dis(gen)];
}

/**
 * @brief Adapt the set of vertices to consider by removing a vertex and its
 * neighbors from the set
 *
 * @param Graph graph
 * @param VertexPtr vertex
 * @param std::unordered_set<VertexPtr> &P
 */
void AdaptGreedyFunction(
    Graph graph,
    VertexPtr vertex,
    std::unordered_set<VertexPtr> &P) // O(n)
{
    P.erase(vertex); // Remove Vertex from the set of vertices to consider
    for (auto [neighbor, edge] : graph.getAdjacencyMatrix()[vertex->getId()])
        P.erase(*(graph.getVertex(neighbor))); // Remove neighbors from the set of vertices to consider
}

/**
 * @brief Construct a random clique of the graph
 *
 * @param Graph graph
 * @return Clique The clique we create
 */
Clique ConstructGreedyRandomizedSolution(Graph graph) // O(n^3)
{
    Clique Solution;
    std::unordered_set<VertexPtr> P = graph.getVertices();

    while (!P.empty())
    {
        std::vector<VertexPtr> RCL = MakeRCL(graph, P); // Restricted Candidate List
        VertexPtr s = SelectElementAtRandom(RCL);
        Solution.addVertex(s); // Add Vertex to the solution we create
        AdaptGreedyFunction(graph, s, P);
    }

    Solution.setWeight(getCliqueWeight(graph, Solution).value());

    return Solution;
}

/**
 * @brief Adapted local search algorithm for the GRASP MEWC algorithm
 * 
 * @param Graph graph
 * @param Clique Solution
 * @return Clique The solution after the local search if it is better
 */
Clique LocalSearchGrasp(Graph graph, Clique Solution)
{
    // TODO
    UNUSED(graph);
    return Solution;
}

/**
 * @brief Update the best solution if the current solution is better
 *
 * @param Clique &Solution
 * @param Clique &BestSolution
 */
void UpdateSolution(Clique &Solution, Clique &BestSolution) // O(1)
{
    if (Solution.getWeight() > BestSolution.getWeight())
        BestSolution = Solution;
}

/**
 * @brief The grasp MEWC algorithm
 *
 * @param Graph g
 * @return Clique The best solution the GRASP can find
 */
Clique graspMEWC(Graph g)
{
    Clique BestSolution;
    Clique Solution;

    for (unsigned short int i = 0; i < RETRIES; i++)
    {
        Solution = ConstructGreedyRandomizedSolution(g); // O(n^3)
        Solution = LocalSearchGrasp(g, Solution);
        UpdateSolution(Solution, BestSolution); // O(1)
    }

    return BestSolution;
}