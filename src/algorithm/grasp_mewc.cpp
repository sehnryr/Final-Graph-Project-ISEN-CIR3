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

#define ALPHA 0.5    // restricted candidate list parameter
#define RETRIES 10   // number of retries for the grasp algorithm
#define TUPLE_SIZE 1 // size of the tuple to consider

/**
 * @brief Returns the sum of the adjacent edges of a vertex
 *
 * @param graph The graph
 * @param vertex The vertex to consider
 * @return long unsigned int The sum of the adjacent edges of a vertex
 */
long unsigned int getSumAdjacentEdges(
    const Graph &graph,
    const VertexPtr &vertex) // O(n)
{
    long unsigned int sum = 0;
    auto adjMatrix = graph.adjacencyMatrix();
    auto neighbors = adjMatrix[vertex->id()];
    for (const auto &[neighbor, edge] : neighbors)
        sum += edge->weight();
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
    const Graph &graph,
    const std::unordered_set<VertexPtr> &vertices) // O(n^2)
{
    long unsigned int gamma = 0;
    auto adjMatrix = graph.adjacencyMatrix();
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
    const Graph &graph,
    const std::unordered_set<VertexPtr> &vertices) // O(n^2)
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
VertexPtr SelectElementAtRandom(const std::vector<VertexPtr> &RCL) // O(1)
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
    const Graph &graph,
    const VertexPtr &vertex,
    std::unordered_set<VertexPtr> &P) // O(n)
{
    auto adjMatrix = graph.adjacencyMatrix();
    auto adjList = adjMatrix[vertex->id()];
    auto P_copy = P;

    P.erase(vertex); // Remove Vertex from the set of vertices to consider
    for (const auto &v : P_copy)
        if (adjList.find(v->id()) == adjList.end())
            P.erase(v); // Remove Vertex's neighbors from the set of vertices to consider
}

/**
 * @brief Construct a random clique of the graph
 *
 * @param Graph graph
 * @return Clique The clique we create
 */
Clique ConstructGreedyRandomizedSolution(const Graph &graph) // O(n^3)
{
    Clique Solution;
    std::unordered_set<VertexPtr> P = graph.vertices();

    while (!P.empty())
    {
        std::vector<VertexPtr> RCL = MakeRCL(graph, P); // Restricted Candidate List
        VertexPtr s = SelectElementAtRandom(RCL);
        Solution.addVertex(s); // Add Vertex to the solution we create
        AdaptGreedyFunction(graph, s, P);
    }

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
    const std::unordered_set<VertexPtr> &vertices,
    std::vector<std::vector<VertexPtr>> &kTuples,
    const std::unordered_set<VertexPtr>::iterator &iter,
    const unsigned int k = TUPLE_SIZE,
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
Clique LocalSearchGrasp(const Graph &graph, Clique Solution)
{
    auto vertices = Solution.vertices();
    std::vector<std::vector<VertexPtr>> kTuples;
    getKTuples(vertices, kTuples, vertices.begin()); // There is k^(n-1) k-tuples of n vertices

    for (auto tuple : kTuples) // O(k^n)
    {
        Graph subgraph = graph;
        for (auto vertex : tuple)
            subgraph.removeVertex(vertex);

        Clique subSolution = localSearchMEWC(subgraph);

        if (subSolution.weight(graph) > Solution.weight(graph))
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
void UpdateSolution(const Graph &graph, Clique &Solution, Clique &BestSolution) // O(1)
{
    if (Solution.weight(graph) > BestSolution.weight(graph))
        BestSolution = Solution;
}

/**
 * @brief The grasp MEWC algorithm
 *
 * @param Graph g
 * @return Clique The best solution the GRASP can find
 */
Clique graspMEWC(const Graph &g)
{
    Clique BestSolution;
    Clique Solution;

    for (unsigned short int i = 0; i < RETRIES; i++)
    {
        Solution = ConstructGreedyRandomizedSolution(g); // O(n^3)
        Solution = LocalSearchGrasp(g, Solution);
        UpdateSolution(g, Solution, BestSolution); // O(1)
    }

    return BestSolution;
}