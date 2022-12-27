#include <map>
#include <vector>

#include "vertex.hpp"

#ifndef CLIQUE_HPP
#define CLIQUE_HPP

class Clique
{
public:
    Clique();
    ~Clique();
    void addEdge(Edge *e);
    std::vector<Vertex *> getVertices() const;
    std::vector<Edge *> getEdges() const;
    bool hasVertex(Vertex *v) const;
    bool hasEdge(Edge *e) const;
    long unsigned int getWeight() const;
    long unsigned int getSize() const;

private:
    std::map<long unsigned int, Vertex *> verticesMap;
    std::vector<Vertex *> vertices;
    std::map<std::pair<long unsigned int, long unsigned int>, Edge *> edgesMap;
    std::vector<Edge *> edges;
    long unsigned int weight;
};

#endif // CLIQUE_HPP