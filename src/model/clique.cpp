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
    : weight(0)
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
        vertices.insert(v);
}

/**
 * @brief Get the vertices of the clique
 *
 * @return std::unordered_set<VertexPtr> The vertices of the clique
 */
std::unordered_set<VertexPtr> Clique::getVertices() const
{
    return vertices;
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
    if (getVertex(v->getId()))
        return true;
    return false;
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
    if (vertices.find(v) != vertices.end())
        return *vertices.find(v);
    return {};
}

/**
 * @brief Set the weight of the clique
 *
 * @param weight The weight of the clique
 */
void Clique::setWeight(long unsigned int weight)
{
    this->weight = weight;
}

/**
 * @brief Add a weight to the clique
 *
 * @param weight The weight to add
 */
void Clique::addWeight(long unsigned int weight)
{
    this->weight += weight;
}

/**
 * @brief Get the weight of the clique
 *
 * @return long unsigned int The weight of the clique
 */
long unsigned int Clique::getWeight() const // Time complexity: O(n^2)
{
    return weight;
}

/**
 * @brief Get the size of the clique
 *
 * @return long unsigned int The size of the clique
 */
long unsigned int Clique::getSize() const
{
    return vertices.size();
}

/**
 * @brief Check if the clique is empty
 *
 * @return true If the clique is empty
 * @return false If the clique is not empty
 */
bool Clique::isEmpty() const
{
    return vertices.empty();
}