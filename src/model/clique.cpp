#include <iostream>

#include "clique.hpp"
#include "../common.hpp"

Clique::Clique()
{
    weight = 0;
}

Clique::~Clique()
{
}

void Clique::addEdge(Edge *e) // Time complexity: O(1)
{
    if (hasVertex(e->getV1()) && hasVertex(e->getV2()))
        return;

    if (!hasVertex(e->getV1()))
    {
        verticesMap[e->getV1()->getId()] = e->getV1();
        vertices.push_back(e->getV1());
    }
    if (!hasVertex(e->getV2()))
    {
        verticesMap[e->getV2()->getId()] = e->getV2();
        vertices.push_back(e->getV2());
    }
    edges.push_back(e);
    weight += e->getWeight();
}

std::vector<Vertex *> Clique::getVertices() const // Time complexity: O(1)
{
    return vertices;
}

bool Clique::hasVertex(Vertex *v) const // Time complexity: O(1)
{
    try
    {
        verticesMap.at(v->getId());
        return true;
    }
    catch (const std::out_of_range &e)
    {
        UNUSED(e);
        return false;
    }
}

long unsigned int Clique::getWeight() const
{
    return weight;
}

long unsigned int Clique::getSize() const
{
    return vertices.size();
}