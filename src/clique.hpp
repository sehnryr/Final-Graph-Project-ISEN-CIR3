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
    int computeWeight() const;
    void setWeight(int weight);
    void addWeight(int weight);
    int getWeight() const;
    int getSize() const;

private:
    std::vector<Vertex *> vertices;
    int weight;
};

#endif // CLIQUE_HPP