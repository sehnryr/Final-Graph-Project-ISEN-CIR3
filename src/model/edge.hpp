#include <memory>
#include <optional>

#include "vertex.hpp"

#ifndef EDGE_HPP
#define EDGE_HPP

/**
 * @brief The Edge class
 * 
 * This class represents an edge in a graph. It contains the two vertices that
 * are connected by the edge and the weight of the edge.
 */
class Edge
{
public:
    Edge(std::shared_ptr<Vertex> v1,
         std::shared_ptr<Vertex> v2,
         unsigned int weight);
    ~Edge();
    std::shared_ptr<Vertex> getV1() const;
    std::shared_ptr<Vertex> getV2() const;
    std::optional<std::shared_ptr<Vertex>> hasVertex(std::shared_ptr<Vertex> v) const;
    std::optional<std::shared_ptr<Vertex>> isIncident(std::shared_ptr<Edge> e) const;
    unsigned int getWeight() const;
    bool operator==(const Edge &e) const;

private:
    std::shared_ptr<Vertex> v1;
    std::shared_ptr<Vertex> v2;
    unsigned int weight;
};

#endif // EDGE_HPP