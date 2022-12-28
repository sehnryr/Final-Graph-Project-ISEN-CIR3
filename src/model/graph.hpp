#include <map>
#include <vector>

#include "vertex.hpp"
#include "edge.hpp"

#ifndef GRAPH_HPP
#define GRAPH_HPP

class Graph
{
public:
    Graph();
    Graph(std::vector<Vertex *> vertices,
          std::vector<Edge *> edges);
    ~Graph();
    void addVertex(Vertex *v);
    void addEdge(Edge *e);
    std::vector<Vertex *> getVertices() const;
    std::vector<Edge *> getEdges() const;
    bool hasVertex(Vertex *v) const;
    bool hasEdge(Edge *e) const;

private:
    std::map<unsigned int, Vertex *> verticesMap;
    std::vector<Vertex *> vertices;
    std::map<std::pair<unsigned int, unsigned int>, Edge *> edgesMap;
    std::vector<Edge *> edges;
};

#endif // GRAPH_HPP