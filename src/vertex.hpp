#include <vector>

#include "edge.hpp"

#ifndef VERTEX_HPP
#define VERTEX_HPP

class Vertex
{
public:
    Vertex(int id);
    ~Vertex();
    int getId() const;
    void addEdge(Edge *e);
    std::vector<Edge *> getEdges() const;
    std::vector<Vertex *> getNeighbors() const;
    bool hasNeighbor(Vertex *v) const;

private:
    int id;
    std::vector<Edge *> edges;
};

#endif // VERTEX_HPP