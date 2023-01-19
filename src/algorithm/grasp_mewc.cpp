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

#define ALPHA 0.5    // restricted candidate list parameter
#define RETRIES 10   // number of retries for the grasp algorithm
#define TUPLE_SIZE 2 // size of the tuple to consider

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
        if (weight > gamma / (1 + ALPHA))
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
    auto adjMatrix = graph.getAdjacencyMatrix();
    auto adjList = adjMatrix[vertex->getId()];
    auto P_copy = P;

    P.erase(vertex); // Remove Vertex from the set of vertices to consider
    for (const auto &v : P_copy)
        if (adjList.find(v->getId()) == adjList.end())
            P.erase(v); // Remove Vertex's neighbors from the set of vertices to consider
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
 * @brief Get all the k-tuples of a set of vertices
 *
 * @param std::unordered_set<VertexPtr> vertices
 * @param std::vector<std::vector<VertexPtr>> &kTuples
 * @param std::unordered_set<VertexPtr>::iterator iter
 * @param int k
 * @param std::vector<VertexPtr> tuple
 */
void getKTuples(
    std::unordered_set<VertexPtr> vertices,
    std::vector<std::vector<VertexPtr>> &kTuples,
    std::unordered_set<VertexPtr>::iterator iter,
    unsigned int k = TUPLE_SIZE,
    std::vector<VertexPtr> tuple = {}) // O(k^n)
{
    if (k == 0 || k > vertices.size())
        return;

    for (auto it = iter; it != vertices.end(); ++it)
    {
        tuple.push_back(*it);
        if (k == 1)
            kTuples.push_back(tuple);
        else
            getKTuples(vertices, kTuples, std::next(it), k - 1, tuple);
        tuple.pop_back();
    }
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
    auto vertices = Solution.getVertices();
    std::vector<std::vector<VertexPtr>> kTuples;
    getKTuples(vertices, kTuples, vertices.begin(), 2); // There is k^(n-1) k-tuples of n vertices

    for (auto tuple : kTuples) // O(k^n)
    {
        Graph subgraph = graph;
        for (auto vertex : tuple)
            subgraph.removeVertex(vertex);

        Clique subSolution = localSearchMEWC(subgraph);

        if (subSolution.getWeight() > Solution.getWeight())
            Solution = subSolution;
    }

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