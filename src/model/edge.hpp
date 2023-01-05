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

// Hash and equal functions for the Edge class and EdgePtr class
namespace std
{
    /**
     * @brief Hash function for the Edge class
     *
     * @param e The edge to hash
     * @return std::size_t The hash of the edge
     */
    template <>
    struct hash<Edge>
    {
        std::size_t operator()(const Edge &e) const
        {
            return hash<unsigned int>()(e.getV1()->getId()) ^
                   hash<unsigned int>()(e.getV2()->getId());
        }
    };

    /**
     * @brief Equal function for the Edge class
     *
     * @param e1 The first edge
     * @param e2 The second edge
     * @return true If the edges are equal
     */
    template <>
    struct equal_to<Edge>
    {
        bool operator()(const Edge &e1, const Edge &e2) const
        {
            return e1 == e2;
        }
    };

    /**
     * @brief Hash function for the EdgePtr class
     *
     * @param e The edge to hash
     * @return std::size_t The hash of the edge
     */
    template <>
    struct hash<EdgePtr>
    {
        std::size_t operator()(const EdgePtr &e) const
        {
            return hash<Edge>()(*e);
        }
    };

    /**
     * @brief Equal function for the EdgePtr class
     *
     * @param e1 The first edge
     * @param e2 The second edge
     * @return true If the edges are equal
     */
    template <>
    struct equal_to<EdgePtr>
    {
        bool operator()(const EdgePtr &e1, const EdgePtr &e2) const
        {
            return *e1 == *e2;
        }
    };
} // namespace std

#endif // EDGE_HPP