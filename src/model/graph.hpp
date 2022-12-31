#include <map>
#include <memory>
#include <optional>
#include <vector>

#include "vertex.hpp"
#include "edge.hpp"

#ifndef GRAPH_HPP
#define GRAPH_HPP

/**
 * @brief The Graph class
 *
 * This class represents a graph. It contains a vector of vertices and a vector
 * of edges. It also contains a map of vertices and a map of edges for faster
 * lookup.
 */
class Graph
{
public:
    Graph();
    ~Graph();
    void addVertex(VertexPtr v);
    void addEdge(EdgePtr);
    std::vector<VertexPtr> getVertices() const;
    std::vector<EdgePtr> getEdges() const;
    bool hasVertex(VertexPtr) const;
    bool hasEdge(EdgePtr) const;
    bool hasEdge(VertexPtr v1, VertexPtr v2) const;
    std::optional<VertexPtr> getVertex(unsigned int id) const;
    std::optional<EdgePtr> getEdge(VertexPtr v1,
                                                 VertexPtr v2) const;
    std::map<unsigned int, std::map<unsigned int, EdgePtr>> getAdjacencyMatrix() const;

private:
    std::map<unsigned int, std::map<unsigned int, EdgePtr>> adjacencyMatrix;
    std::map<unsigned int, VertexPtr> verticesMap;
    std::vector<VertexPtr> vertices;
    std::vector<EdgePtr> edges;
};

#endif // GRAPH_HPP