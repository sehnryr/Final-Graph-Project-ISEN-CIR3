#include <map>
#include <memory>
#include <optional>
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
    void addVertex(std::shared_ptr<Vertex> v);
    void addEdge(std::shared_ptr<Edge>);
    std::vector<std::shared_ptr<Vertex>> getVertices() const;
    std::vector<std::shared_ptr<Edge>> getEdges() const;
    bool hasVertex(std::shared_ptr<Vertex>) const;
    bool hasEdge(std::shared_ptr<Edge>) const;
    std::optional<std::shared_ptr<Vertex>> getVertex(unsigned int id) const;
    std::optional<std::shared_ptr<Edge>> getEdge(std::shared_ptr<Vertex> v1,
                                                 std::shared_ptr<Vertex> v2) const;
    std::map<unsigned int, std::map<unsigned int, std::shared_ptr<Edge>>> getAdjacencyMatrix() const;

private:
    std::map<unsigned int, std::map<unsigned int, std::shared_ptr<Edge>>> adjacencyMatrix;
    std::map<unsigned int, std::shared_ptr<Vertex>> verticesMap;
    std::vector<std::shared_ptr<Vertex>> vertices;
    std::vector<std::shared_ptr<Edge>> edges;
};

#endif // GRAPH_HPP