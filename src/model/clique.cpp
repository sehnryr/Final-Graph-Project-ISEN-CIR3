#include "clique.hpp"

Clique::Clique()
{
    weight = 0;
}

Clique::~Clique()
{
}

void Clique::addVertex(Vertex *v)
{
    vertices.push_back(v);
}

std::vector<Vertex *> Clique::getVertices() const
{
    return vertices;
}

bool Clique::hasVertex(Vertex *v) const
{
    for (auto &vertex : vertices)
        if (vertex == v)
            return true;
    return false;
}

long unsigned int Clique::computeWeight() const
{
    // if an edge exists between two vertices in the clique, add its weight to the total
    long unsigned int weight = 0;
    for (auto &vertex : vertices)
        for (auto &e : vertex->getEdges())
            if (hasVertex(e->getV1() == vertex ? e->getV2() : e->getV1()))
                weight += e->getWeight();
    
    // divide by two because each edge is counted twice
    return weight / 2;
}

void Clique::setWeight(long unsigned int weight)
{
    this->weight = weight;
}

void Clique::addWeight(long unsigned int weight)
{
    this->weight += weight;
}

long unsigned int Clique::getWeight() const
{
    return weight;
}

long unsigned int Clique::getSize() const
{
    return vertices.size();
}