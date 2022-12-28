#include <map>
#include <optional>
#include <vector>

#include "edge.hpp"

#ifndef VERTEX_HPP
#define VERTEX_HPP

class Vertex
{
public:
    Vertex(unsigned int id);
    ~Vertex();
    unsigned int getId() const;
    void addEdge(Edge *e);
    std::vector<Edge *> getEdges() const;
    std::vector<Vertex *> getNeighbors() const;
    std::optional<Edge *> hasNeighbor(Vertex *v) const;

private:
    unsigned int id;
    std::map<long unsigned int, Edge *> edgesMap;
    std::vector<Edge *> edges;
    std::vector<Vertex *> neighbors;
};

#endif // VERTEX_HPP