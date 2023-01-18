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
Edge::Edge(VertexPtr v1, VertexPtr v2, unsigned int weight)
    : v1(v1), v2(v2), weight(weight)
{
}

/**
 * @brief Destroy the Edge:: Edge object
 */
Edge::~Edge()
{
}