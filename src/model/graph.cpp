#include <iostream>

#include "graph.hpp"
#include "../common.hpp"

/**
 * @brief Construct a new Graph:: Graph object
 */
Graph::Graph()
{
}

/**
 * @brief Destroy the Graph:: Graph object
 */
Graph::~Graph()
{
}

/**
 * @brief Add a vertex to the graph
 *
 * This method adds a vertex to the graph. If the vertex already exists, it does
 * nothing.
 *
 * @param v The vertex to add
 */
void Graph::addVertex(std::shared_ptr<Vertex> v) // Time complexity: O(1)
{
    // If the vertex already exists, do nothing
    if (hasVertex(v))
        return;

    verticesMap[v->getId()] = v;
    vertices.push_back(v);
}

/**
 * @brief Add an edge to the graph
 *
 * This method adds an edge to the graph. If the edge already exists, it does
 * nothing. Since we are considering simple undirected graphs, we need to add the
 * edge to the adjacency matrix in both directions.
 *
 * @param e The edge to add
 */
void Graph::addEdge(std::shared_ptr<Edge> e) // Time complexity: O(1)
{
    // If the edge already exists, do nothing
    if (hasEdge(e))
        return;

    edges.push_back(e);
    // Considering simple undirected graphs (no parallel edges and no self-loops)
    // we need to add the edge to the adjacency matrix in both directions
    adjacencyMatrix[e->getV1()->getId()][e->getV2()->getId()] = e;
    adjacencyMatrix[e->getV2()->getId()][e->getV1()->getId()] = e;
}

/**
 * @brief Get the vertices of the graph
 *
 * @return std::vector<std::shared_ptr<Vertex>> The vertices of the graph
 */
std::vector<std::shared_ptr<Vertex>> Graph::getVertices() const // Time complexity: O(1)
{
    return vertices;
}

/**
 * @brief Get the edges of the graph
 *
 * @return std::vector<std::shared_ptr<Edge>> The edges of the graph
 */
std::vector<std::shared_ptr<Edge>> Graph::getEdges() const // Time complexity: O(1)
{
    return edges;
}

/**
 * @brief Check if a vertex is in the graph
 *
 * @param v The vertex to check
 * @return true If the vertex is in the graph, false otherwise
 */
bool Graph::hasVertex(std::shared_ptr<Vertex> v) const // Time complexity: O(1)
{
    if (getVertex(v->getId()))
        return true;
    return false;
}

/**
 * @brief Check if an edge is in the graph
 *
 * @param e The edge to check
 * @return true If the edge is in the graph, false otherwise
 */
bool Graph::hasEdge(std::shared_ptr<Edge> e) const // Time complexity: O(1)
{
    return hasEdge(e->getV1(), e->getV2());
}

/**
 * @brief Check if an edge is in the graph
 *
 * @param v1 The first vertex of the edge
 * @param v2 The second vertex of the edge
 * @return true If the edge is in the graph, false otherwise
 */
bool Graph::hasEdge(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2) const // Time complexity: O(1)
{
    if (getEdge(v1, v2))
        return true;
    return false;
}

/**
 * @brief Get a vertex from the graph
 *
 * This method returns a vertex from the graph if it exists. If it does, it returns
 * the vertex as an optional. If it does not, it returns an empty optional.
 *
 * @param id The id of the vertex
 * @return std::optional<std::shared_ptr<Vertex>> The vertex if it exists,
 * an empty optional otherwise
 */
std::optional<std::shared_ptr<Vertex>> Graph::getVertex(unsigned int id) const // Time complexity: O(1)
{
    try
    {
        return verticesMap.at(id);
    }
    catch (const std::out_of_range &e)
    {
        UNUSED(e);
        return {};
    }
}

/**
 * @brief Get an edge from the graph
 *
 * This method returns an edge from the graph if it exists. If it does, it returns
 * the edge as an optional. If it does not, it returns an empty optional.
 *
 * @param v1 The first vertex of the edge
 * @param v2 The second vertex of the edge
 * @return std::optional<std::shared_ptr<Edge>> The edge if it exists,
 * an empty optional otherwise
 */
std::optional<std::shared_ptr<Edge>> Graph::getEdge(std::shared_ptr<Vertex> v1,
                                                    std::shared_ptr<Vertex> v2) const // Time complexity: O(1)
{
    try
    {
        return adjacencyMatrix.at(v1->getId()).at(v2->getId());
    }
    catch (const std::out_of_range &e)
    {
        UNUSED(e);
        return {};
    }
}

/**
 * @brief Get the adjacency matrix of the graph
 *
 * @return std::map<unsigned int, std::map<unsigned int, std::shared_ptr<Edge>>> The adjacency matrix
 */
std::map<unsigned int, std::map<unsigned int, std::shared_ptr<Edge>>> Graph::getAdjacencyMatrix() const // Time complexity: O(1)
{
    return adjacencyMatrix;
}