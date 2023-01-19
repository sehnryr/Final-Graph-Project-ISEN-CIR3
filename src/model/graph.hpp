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

    // Set methods
    void addVertex(VertexPtr v);
    void addEdge(EdgePtr);

    // Get methods
    std::optional<VertexPtr> getVertex(unsigned int id) const;
    std::optional<EdgePtr> getEdge(unsigned int id1, unsigned int id2) const;
    std::optional<EdgePtr> getEdge(VertexPtr v1, VertexPtr v2) const;

    inline std::unordered_set<VertexPtr> getVertices() const { return _vertices; };
    inline std::unordered_set<EdgePtr> getEdges() const { return _edges; };
    inline std::unordered_map<unsigned int, std::unordered_map<unsigned int, EdgePtr>>
    getAdjacencyMatrix() const { return _adjacencyMatrix; };

    inline std::unordered_set<VertexPtr> vertices() const { return _vertices; };
    inline std::unordered_set<EdgePtr> edges() const { return _edges; };
    inline std::unordered_map<unsigned int, std::unordered_map<unsigned int, EdgePtr>>
    adjacencyMatrix() const { return _adjacencyMatrix; };

    inline long unsigned int getSize() const { return _vertices.size(); }

    inline long unsigned int size() const { return _vertices.size(); }

    // Boolean methods
    bool hasVertex(unsigned int id) const;
    bool hasVertex(VertexPtr v) const;
    bool hasEdge(unsigned int id1, unsigned int id2) const;
    bool hasEdge(VertexPtr v1, VertexPtr v2) const;
    bool hasEdge(EdgePtr e) const;

    inline bool isEmpty() const { return _vertices.empty(); }

    inline bool empty() const { return _vertices.empty(); }

    // Remove methods
    const std::optional<VertexPtr> removeVertex(unsigned int id);
    const std::optional<VertexPtr> removeVertex(VertexPtr v);
    const std::optional<EdgePtr> removeEdge(unsigned int id1, unsigned int id2);
    const std::optional<EdgePtr> removeEdge(VertexPtr v1, VertexPtr v2);
    const std::optional<EdgePtr> removeEdge(EdgePtr e);

private:
    std::unordered_map<unsigned int, std::unordered_map<unsigned int, EdgePtr>>
        _adjacencyMatrix;
    std::unordered_set<VertexPtr> _vertices;
    std::unordered_set<EdgePtr> _edges;
};

#endif // GRAPH_HPP