#include <vector>

#include "vertex.hpp"

#ifndef CLIQUE_HPP
#define CLIQUE_HPP

class Clique
{
public:
    Clique();
    ~Clique();
    void addVertex(Vertex *v);
    std::vector<Vertex *> getVertices() const;
    bool hasVertex(Vertex *v) const;
    long unsigned int computeWeight() const;
    void setWeight(long unsigned int weight);
    void addWeight(long unsigned int weight);
    long unsigned int getWeight() const;
    long unsigned int getSize() const;

private:
    std::vector<Vertex *> vertices;
    long unsigned int weight;
};

#endif // CLIQUE_HPP