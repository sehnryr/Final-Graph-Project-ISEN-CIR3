/**
 * @file clique.cpp
 * @brief Implementation of the Clique class
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-26
 */

#include <iostream>

#include "clique.hpp"
#include "../common.hpp"

/**
 * @brief Construct a new Clique:: Clique object
 */
Clique::Clique()
    : _weight(0)
{
}

/**
 * @brief Destroy the Clique:: Clique object
 */
Clique::~Clique()
{
}

/**
 * @brief Add a vertex to the clique
 *
 * This method adds a vertex to the clique. If the vertex is already in the clique,
 * it does nothing.
 *
 * @param v The vertex to add
 */
void Clique::addVertex(VertexPtr v)
{
    if (!hasVertex(v))
        _vertices.insert(v);
}

/**
 * @brief Check if the clique contains a vertex
 *
 * @param id The id of the vertex to check
 * @return true If the vertex is in the clique
 * @return false If the vertex is not in the clique
 */
bool Clique::hasVertex(unsigned int id) const // Time complexity: O(1)
{
    if (getVertex(id))
        return true;
    return false;
}

/**
 * @brief Check if the clique contains a vertex
 *
 * @param v The vertex to check
 * @return true If the vertex is in the clique
 * @return false If the vertex is not in the clique
 */
bool Clique::hasVertex(VertexPtr v) const // Time complexity: O(1)
{
    return hasVertex(v->getId());
}

/**
 * @brief Get a vertex from the clique
 *
 * This method returns a vertex from the graph if it exists. If it does, it returns
 * the vertex as an optional. If it does not, it returns an empty optional.
 *
 * @param id The id of the vertex to get
 * @return std::optional<VertexPtr> The vertex if it exists, an empty
 * optional otherwise
 */
std::optional<VertexPtr> Clique::getVertex(unsigned int id) const // Time complexity: O(1)
{
    VertexPtr v = std::make_shared<Vertex>(id);
    if (_vertices.find(v) != _vertices.end())
        return *_vertices.find(v);
    return {};
}