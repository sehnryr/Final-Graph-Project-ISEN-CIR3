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

#define GraphPtr std::shared_ptr<Graph>

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
    inline void addVertex(const VertexPtr &v) { _vertices.insert(v); }
    inline void addEdge(const EdgePtr &e)
    {
        _edges.insert(e);
        // Considering simple undirected graphs (no parallel edges and no self-loops)
        // we need to add the edge to the adjacency matrix in both directions
        _adjacencyMatrix[e->first()->id()][e->second()->id()] = e;
        _adjacencyMatrix[e->second()->id()][e->first()->id()] = e;
    }

    // Get methods
    const std::optional<VertexPtr> getVertex(unsigned int id) const;
    const std::optional<EdgePtr> getEdge(unsigned int first_id, unsigned int second_id) const;
    const std::optional<EdgePtr> getEdge(const VertexPtr &first, const VertexPtr &second) const;

    inline const std::unordered_set<VertexPtr> vertices() const { return _vertices; };
    inline const std::unordered_set<EdgePtr> edges() const { return _edges; };
    inline const std::unordered_map<unsigned int, std::unordered_map<unsigned int, EdgePtr>>
    adjacencyMatrix() const { return _adjacencyMatrix; };

    inline long unsigned int size() const { return _vertices.size(); }

    // Boolean methods
    bool hasVertex(unsigned int id) const;
    bool hasVertex(const VertexPtr &v) const;
    bool hasEdge(unsigned int first_id, unsigned int second_id) const;
    bool hasEdge(const VertexPtr &first, const VertexPtr &second) const;
    bool hasEdge(const EdgePtr &e) const;

    inline bool empty() const { return _vertices.empty(); }

    // Remove methods
    const std::optional<VertexPtr> removeVertex(unsigned int id);
    const std::optional<VertexPtr> removeVertex(const VertexPtr &v);
    const std::optional<EdgePtr> removeEdge(unsigned int first_id, unsigned int second_id);
    const std::optional<EdgePtr> removeEdge(const VertexPtr &first, const VertexPtr &second);
    const std::optional<EdgePtr> removeEdge(const EdgePtr &e);

protected:
    std::unordered_map<unsigned int, std::unordered_map<unsigned int, EdgePtr>>
        _adjacencyMatrix;
    std::unordered_set<VertexPtr> _vertices;
    std::unordered_set<EdgePtr> _edges;
};

#endif // GRAPH_HPP