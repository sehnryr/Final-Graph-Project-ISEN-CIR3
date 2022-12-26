#include <vector>

#include "vertex.hpp"
#include "edge.hpp"

#ifndef GRAPH_HPP
#define GRAPH_HPP

class Graph
{
public:
    Graph();
    ~Graph();
    void addVertex(Vertex *v);
    void addEdge(Edge *e);
    std::vector<Vertex *> getVertices() const;
    std::vector<Edge *> getEdges() const;

private:
    std::vector<Vertex *> vertices;
    std::vector<Edge *> edges;
};

#endif // GRAPH_HPP