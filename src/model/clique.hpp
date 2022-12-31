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
    void addVertex(VertexPtr v);
    std::unordered_set<VertexPtr> getVertices() const;
    bool hasVertex(VertexPtr v) const;
    std::optional<VertexPtr> getVertex(unsigned int id) const;
    void setWeight(long unsigned int weight);
    void addWeight(long unsigned int weight);
    long unsigned int getWeight() const;
    long unsigned int getSize() const;
    bool isEmpty() const;

private:
    std::unordered_set<VertexPtr> vertices;
    long unsigned int weight;
};

#endif // CLIQUE_HPP