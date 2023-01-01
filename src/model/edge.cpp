/**
 * @file edge.cpp
 * @brief Implementation of the Edge class
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-26
 */

#include "edge.hpp"

/**
 * @brief Construct a new Edge:: Edge object
 *
 * @param v1 The first vertex
 * @param v2 The second vertex
 * @param weight The weight of the edge
 */
Edge::Edge(VertexPtr v1,
           VertexPtr v2,
           unsigned int weight)
{
    this->v1 = v1;
    this->v2 = v2;
    this->weight = weight;
}

/**
 * @brief Destroy the Edge:: Edge object
 */
Edge::~Edge()
{
}

/**
 * @brief Get the first vertex
 *
 * @return VertexPtr The first vertex
 */
VertexPtr Edge::getV1() const
{
    return v1;
}

/**
 * @brief Get the second vertex
 *
 * @return VertexPtr The second vertex
 */
VertexPtr Edge::getV2() const
{
    return v2;
}

/**
 * @brief Check if the edge has a vertex
 *
 * This method checks if the edge has a vertex. If it does, it returns the vertex
 * as an optional. If it doesn't, it returns an empty optional.
 *
 * @param v The vertex to check
 * @return std::optional<VertexPtr> The vertex if the edge has it,
 * otherwise an empty optional
 */
std::optional<VertexPtr> Edge::hasVertex(VertexPtr v) const
{
    if (v1 == v)
        return v1;
    if (v2 == v)
        return v2;
    return {};
}

/**
 * @brief Check if the edge is incident to another edge
 *
 * This method checks if the edge is incident to another edge. If it is, it
 * returns the vertex that is incident to both edges as an optional. If it isn't,
 * it returns an empty optional.
 *
 * @param e The edge to check
 * @return std::optional<VertexPtr> The vertex if the edge is
 * incident to the other edge, otherwise an empty optional
 */
std::optional<VertexPtr> Edge::isIncident(EdgePtr e) const
{
    if (auto v = hasVertex(e->getV1()))
        return *v;
    if (auto v = hasVertex(e->getV2()))
        return *v;
    return {};
}

/**
 * @brief Get the weight of the edge
 *
 * @return unsigned int The weight of the edge
 */
unsigned int Edge::getWeight() const
{
    return weight;
}

/**
 * @brief Compare two edges
 *
 * This method compares two edges. It returns true if the edges have the same
 * vertices in the same order. Otherwise, it returns false.
 *
 * @param e The edge to compare to
 * @return true If the edges have the same vertices
 * @return false If the edges have different vertices
 */
bool Edge::operator==(const Edge &e) const
{
    return v1 == e.v1 && v2 == e.v2;
}