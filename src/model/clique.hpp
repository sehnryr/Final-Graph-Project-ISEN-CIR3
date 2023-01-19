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
class Clique : public Graph
{
public:
    Clique(Graph g);
    Clique(GraphPtr g);
    ~Clique();

    // Set methods
    void addVertex(VertexPtr v);

    // Get methods
    long unsigned int weight();

private:
    GraphPtr _graph;
    long unsigned int _weight;
    bool _modified;
};

#endif // CLIQUE_HPP