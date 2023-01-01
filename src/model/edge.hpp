/**
 * @file edge.hpp
 * @brief Declaration of the Edge class
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-26
 */

#include <memory>
#include <optional>

#include "vertex.hpp"

#ifndef EDGE_HPP
#define EDGE_HPP

#define EdgePtr std::shared_ptr<Edge>

/**
 * @brief The Edge class
 *
 * This class represents an edge in a graph. It contains the two vertices that
 * are connected by the edge and the weight of the edge.
 */
class Edge
{
public:
    Edge(VertexPtr v1,
         VertexPtr v2,
         unsigned int weight);
    ~Edge();
    VertexPtr getV1() const;
    VertexPtr getV2() const;
    std::optional<VertexPtr> hasVertex(VertexPtr v) const;
    std::optional<VertexPtr> isIncident(EdgePtr e) const;
    unsigned int getWeight() const;
    bool operator==(const Edge &e) const;

private:
    VertexPtr v1;
    VertexPtr v2;
    unsigned int weight;
};

#endif // EDGE_HPP