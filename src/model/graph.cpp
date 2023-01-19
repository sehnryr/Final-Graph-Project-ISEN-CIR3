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
const std::optional<VertexPtr> Graph::getVertex(unsigned int id) const // Time complexity: O(1)
{
    VertexPtr v = std::make_shared<Vertex>(id);
    if (_vertices.find(v) != _vertices.end())
        return *_vertices.find(v);
    return {};
}

/**
 * @brief Get an edge from the graph
 *
 * @param first_id The id of the first vertex of the edge
 * @param second_id The id of the second vertex of the edge
 * @return std::optional<EdgePtr> The edge if it exists,
 */
const std::optional<EdgePtr> Graph::getEdge(
    unsigned int first_id,
    unsigned int second_id) const // Time complexity: O(1)
{
    try
    {
        return _adjacencyMatrix.at(first_id).at(second_id);
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
 * @param first The first vertex of the edge
 * @param second The second vertex of the edge
 * @return std::optional<EdgePtr> The edge if it exists,
 * an empty optional otherwise
 */
const std::optional<EdgePtr> Graph::getEdge(
    const VertexPtr &first,
    const VertexPtr &second) const // Time complexity: O(1)
{
    return getEdge(first->id(), second->id());
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
bool Graph::hasVertex(const VertexPtr &v) const // Time complexity: O(1)
{
    return hasVertex(v->id());
}

/**
 * @brief Check if an edge is in the graph
 *
 * @param first_id The id of the first vertex of the edge
 * @param second_id The id of the second vertex of the edge
 * @return true If the edge is in the graph, false otherwise
 */
bool Graph::hasEdge(unsigned int first_id, unsigned int second_id) const // Time complexity: O(1)
{
    if (getEdge(first_id, second_id))
        return true;
    return false;
}

/**
 * @brief Check if an edge is in the graph
 *
 * @param first The first vertex of the edge
 * @param second The second vertex of the edge
 * @return true If the edge is in the graph, false otherwise
 */
bool Graph::hasEdge(const VertexPtr &first, const VertexPtr &second) const // Time complexity: O(1)
{
    return hasEdge(first->id(), second->id());
}

/**
 * @brief Check if an edge is in the graph
 *
 * @param e The edge to check
 * @return true If the edge is in the graph, false otherwise
 */
bool Graph::hasEdge(const EdgePtr &e) const // Time complexity: O(1)
{
    return hasEdge(e->first(), e->second());
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
const std::optional<VertexPtr> Graph::removeVertex(const VertexPtr &v)
{
    return removeVertex(v->id());
}

/**
 * @brief Remove an edge from the graph
 *
 * @param first_id The id of the first vertex of the edge
 * @param second_id The id of the second vertex of the edge
 * @return std::optional<EdgePtr> The edge if it was removed, an empty optional otherwise
 */
const std::optional<EdgePtr> Graph::removeEdge(unsigned int first_id, unsigned int second_id)
{
    // Check if the edge exists
    if (!hasEdge(first_id, second_id))
        return {};

    EdgePtr edge = getEdge(first_id, second_id).value();
    _adjacencyMatrix[first_id].erase(second_id);
    _adjacencyMatrix[second_id].erase(first_id);

    return edge;
}

/**
 * @brief Remove an edge from the graph
 *
 * @param first The first vertex of the edge
 * @param second The second vertex of the edge
 * @return std::optional<EdgePtr> The edge if it was removed, an empty optional otherwise
 */
const std::optional<EdgePtr> Graph::removeEdge(const VertexPtr &first, const VertexPtr &second)
{
    return removeEdge(first->id(), second->id());
}

/**
 * @brief Remove an edge from the graph
 *
 * @param e The edge to remove
 * @return std::optional<EdgePtr> The edge if it was removed, an empty optional otherwise
 */
const std::optional<EdgePtr> Graph::removeEdge(const EdgePtr &e)
{
    return removeEdge(e->first(), e->second());
}
