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
 * @param first The first vertex
 * @param second The second vertex
 * @param weight The weight of the edge
 */
Edge::Edge(VertexPtr first, VertexPtr second, unsigned int weight)
    : _first(first), _second(second), _weight(weight)
{
}

/**
 * @brief Destroy the Edge:: Edge object
 */
Edge::~Edge()
{
}