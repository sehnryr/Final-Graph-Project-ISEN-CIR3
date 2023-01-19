/**
 * @file clique.hpp
 * @brief Declaration of the Clique class
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-26
 */

#include <memory>
#include <optional>
#include <unordered_set>

#include "graph.hpp"
#include "edge.hpp"
#include "vertex.hpp"

#ifndef CLIQUE_HPP
#define CLIQUE_HPP

/**
 * @brief The Clique class
 *
 * This class represents a clique in a graph. A clique is a subset of vertices
 * that are all connected to each other. It contains a unordered_set of vertices
 * for faster lookup. It also contains the weight of the clique.
 * The weight is not calculated by the class itself, but is set by the user.
 */
class Clique
{
public:
    Clique();
    ~Clique();

    // Set methods
    void addVertex(VertexPtr v);
    inline void setWeight(long unsigned int weight) { this->_weight = weight; }
    inline void addWeight(long unsigned int weight) { this->_weight += weight; }

    // Get methods
    std::optional<VertexPtr> getVertex(unsigned int id) const;

    inline std::unordered_set<VertexPtr> vertices() const { return _vertices; }

    inline long unsigned int weight() const { return _weight; }
    inline long unsigned int size() const { return _vertices.size(); }

    // Boolean methods
    bool hasVertex(unsigned int id) const;
    bool hasVertex(VertexPtr v) const;

    inline bool empty() const { return _vertices.empty(); }

private:
    std::unordered_set<VertexPtr> _vertices;
    long unsigned int _weight;
};

#endif // CLIQUE_HPP