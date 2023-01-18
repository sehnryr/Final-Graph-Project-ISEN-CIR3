/**
 * @file graph.cpp
 * @brief Implementation of the Graph class
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-26
 */

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
void Graph::addVertex(VertexPtr v) // Time complexity: O(1)
{
    // If the vertex already exists, do nothing
    if (hasVertex(v))
        return;

    vertices.insert(v);
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
void Graph::addEdge(EdgePtr e) // Time complexity: O(1)
{
    // If the edge already exists, do nothing
    if (hasEdge(e))
        return;

    edges.insert(e);
    // Considering simple undirected graphs (no parallel edges and no self-loops)
    // we need to add the edge to the adjacency matrix in both directions
    adjacencyMatrix[e->getV1()->getId()][e->getV2()->getId()] = e;
    adjacencyMatrix[e->getV2()->getId()][e->getV1()->getId()] = e;
}

/**
 * @brief Check if a vertex is in the graph
 *
 * @param v The vertex to check
 * @return true If the vertex is in the graph, false otherwise
 */
bool Graph::hasVertex(VertexPtr v) const // Time complexity: O(1)
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
bool Graph::hasEdge(EdgePtr e) const // Time complexity: O(1)
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
bool Graph::hasEdge(VertexPtr v1, VertexPtr v2) const // Time complexity: O(1)
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
 * @return std::optional<VertexPtr> The vertex if it exists,
 * an empty optional otherwise
 */
std::optional<VertexPtr> Graph::getVertex(unsigned int id) const // Time complexity: O(1)
{
    VertexPtr v = std::make_shared<Vertex>(id);
    if (vertices.find(v) != vertices.end())
        return *vertices.find(v);
    return {};
}

/**
 * @brief Get an edge from the graph
 *
 * This method returns an edge from the graph if it exists. If it does, it returns
 * the edge as an optional. If it does not, it returns an empty optional.
 *
 * @param v1 The first vertex of the edge
 * @param v2 The second vertex of the edge
 * @return std::optional<EdgePtr> The edge if it exists,
 * an empty optional otherwise
 */
std::optional<EdgePtr> Graph::getEdge(
    VertexPtr v1,
    VertexPtr v2) const // Time complexity: O(1)
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
 * @brief Remove a vertex from the graph and all its incident edges
 *
 * @param id The id of the vertex to remove
 * @return std::optional<VertexPtr> The vertex if it was removed, an empty optional otherwise
 */
const std::optional<VertexPtr> Graph::removeVertex(unsigned int id)
{
    // Delete the vertex from the set of vertices
    VertexPtr v = std::make_shared<Vertex>(id);
    if (!hasVertex(v))
        return {};

    vertices.erase(v);

    // Delete the vertex from the adjacency matrix and the set of edges
    for (const auto &[neighbor, edge] : adjacencyMatrix[id])
    {
        adjacencyMatrix[neighbor].erase(id);
        edges.erase(edge);
    }
    adjacencyMatrix.erase(id);

    return v;
}

/**
 * @brief Remove a vertex from the graph and all its incident edges
 *
 * @param v The vertex to remove
 * @return std::optional<VertexPtr> The vertex if it was removed, an empty optional otherwise
 */
const std::optional<VertexPtr> Graph::removeVertex(VertexPtr v)
{
    return removeVertex(v->getId());
}

/**
 * @brief Remove an edge from the graph
 *
 * @param id1 The id of the first vertex of the edge
 * @param id2 The id of the second vertex of the edge
 * @return std::optional<EdgePtr> The edge if it was removed, an empty optional otherwise
 */
const std::optional<EdgePtr> Graph::removeEdge(unsigned int id1, unsigned int id2)
{
    // Check if the vertices exist
    if (adjacencyMatrix.find(id1) == adjacencyMatrix.end() ||
        adjacencyMatrix.find(id2) == adjacencyMatrix.end())
        return {};

    return removeEdge(getVertex(id1).value(), getVertex(id2).value());
}

/**
 * @brief Remove an edge from the graph
 *
 * @param v1 The first vertex of the edge
 * @param v2 The second vertex of the edge
 * @return std::optional<EdgePtr> The edge if it was removed, an empty optional otherwise
 */
const std::optional<EdgePtr> Graph::removeEdge(VertexPtr v1, VertexPtr v2)
{
    // Check if the edge exists
    if (!hasEdge(v1, v2))
        return {};

    EdgePtr edge = adjacencyMatrix[v1->getId()][v2->getId()];
    adjacencyMatrix[v1->getId()].erase(v2->getId());
    adjacencyMatrix[v2->getId()].erase(v1->getId());

    return edge;
}

/**
 * @brief Remove an edge from the graph
 *
 * @param e The edge to remove
 * @return std::optional<EdgePtr> The edge if it was removed, an empty optional otherwise
 */
const std::optional<EdgePtr> Graph::removeEdge(EdgePtr e)
{
    return removeEdge(e->getV1(), e->getV2());
}
