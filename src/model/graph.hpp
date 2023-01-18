/**
 * @file graph.hpp
 * @brief Declaration of the Graph class
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-26
 */

#include <memory>
#include <optional>
#include <unordered_map>
#include <unordered_set>

#include "vertex.hpp"
#include "edge.hpp"

#ifndef GRAPH_HPP
#define GRAPH_HPP

/**
 * @brief The Graph class
 *
 * This class represents a graph. It contains a set of vertices and a set
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
    std::unordered_set<VertexPtr> getVertices() const;
    std::unordered_set<EdgePtr> getEdges() const;
    bool hasVertex(VertexPtr) const;
    bool hasEdge(EdgePtr) const;
    bool hasEdge(VertexPtr v1, VertexPtr v2) const;
    std::optional<VertexPtr> getVertex(unsigned int id) const;
    std::optional<EdgePtr> getEdge(VertexPtr v1,
                                   VertexPtr v2) const;
    std::unordered_map<unsigned int, std::unordered_map<unsigned int, EdgePtr>>
    getAdjacencyMatrix() const;

    // Remove methods
    std::optional<VertexPtr> removeVertex(unsigned int id);
    std::optional<VertexPtr> removeVertex(VertexPtr v);
    std::optional<EdgePtr> removeEdge(unsigned int id1, unsigned int id2);
    std::optional<EdgePtr> removeEdge(VertexPtr v1, VertexPtr v2);
    std::optional<EdgePtr> removeEdge(EdgePtr e);

private:
    std::unordered_map<unsigned int, std::unordered_map<unsigned int, EdgePtr>>
        adjacencyMatrix;
    std::unordered_set<VertexPtr> vertices;
    std::unordered_set<EdgePtr> edges;
};

#endif // GRAPH_HPP