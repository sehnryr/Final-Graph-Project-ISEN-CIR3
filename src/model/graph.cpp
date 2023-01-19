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

/* SET METHODS */

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

    _vertices.insert(v);
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

    _edges.insert(e);
    // Considering simple undirected graphs (no parallel edges and no self-loops)
    // we need to add the edge to the adjacency matrix in both directions
    _adjacencyMatrix[e->getV1()->getId()][e->getV2()->getId()] = e;
    _adjacencyMatrix[e->getV2()->getId()][e->getV1()->getId()] = e;
}

/* GET METHODS */

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
    if (_vertices.find(v) != _vertices.end())
        return *_vertices.find(v);
    return {};
}

/**
 * @brief Get an edge from the graph
 *
 * @param id1 The id of the first vertex of the edge
 * @param id2 The id of the second vertex of the edge
 * @return std::optional<EdgePtr> The edge if it exists,
 */
std::optional<EdgePtr> Graph::getEdge(
    unsigned int id1,
    unsigned int id2) const // Time complexity: O(1)
{
    try
    {
        return _adjacencyMatrix.at(id1).at(id2);
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
 * @return std::optional<EdgePtr> The edge if it exists,
 * an empty optional otherwise
 */
std::optional<EdgePtr> Graph::getEdge(
    VertexPtr v1,
    VertexPtr v2) const // Time complexity: O(1)
{
    return getEdge(v1->getId(), v2->getId());
}

/* BOOLEAN METHODS */

/**
 * @brief Check if a vertex is in the graph
 *
 * @param id The id of the vertex to check
 * @return true If the vertex is in the graph, false otherwise
 */
bool Graph::hasVertex(unsigned int id) const // Time complexity: O(1)
{
    if (getVertex(id))
        return true;
    return false;
}

/**
 * @brief Check if a vertex is in the graph
 *
 * @param v The vertex to check
 * @return true If the vertex is in the graph, false otherwise
 */
bool Graph::hasVertex(VertexPtr v) const // Time complexity: O(1)
{
    return hasVertex(v->getId());
}

/**
 * @brief Check if an edge is in the graph
 *
 * @param id1 The id of the first vertex of the edge
 * @param id2 The id of the second vertex of the edge
 * @return true If the edge is in the graph, false otherwise
 */
bool Graph::hasEdge(unsigned int id1, unsigned int id2) const // Time complexity: O(1)
{
    if (getEdge(id1, id2))
        return true;
    return false;
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
    return hasEdge(v1->getId(), v2->getId());
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

/* REMOVE METHODS */

/**
 * @brief Remove a vertex from the graph and all its incident edges
 *
 * @param id The id of the vertex to remove
 * @return std::optional<VertexPtr> The vertex if it was removed, an empty optional otherwise
 */
const std::optional<VertexPtr> Graph::removeVertex(unsigned int id)
{
    // If the vertex does not exist, do nothing
    if (!hasVertex(id))
        return {};

    // Get the vertex
    VertexPtr v = getVertex(id).value();

    // Delete the vertex from the set of vertices
    _vertices.erase(v);

    // Delete the vertex from the adjacency matrix and the set of edges
    for (const auto &[neighbor, edge] : _adjacencyMatrix[id])
    {
        _adjacencyMatrix[neighbor].erase(id);
        _edges.erase(edge);
    }
    _adjacencyMatrix.erase(id);

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
    // Check if the edge exists
    if (!hasEdge(id1, id2))
        return {};

    EdgePtr edge = getEdge(id1, id2).value();
    _adjacencyMatrix[id1].erase(id2);
    _adjacencyMatrix[id2].erase(id1);

    return edge;
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
    return removeEdge(v1->getId(), v2->getId());
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
