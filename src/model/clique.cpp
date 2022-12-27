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
    edgesMap[std::make_pair(e->getV1()->getId(), e->getV2()->getId())] = e;
    weight += e->getWeight();
}

std::vector<Vertex *> Clique::getVertices() const // Time complexity: O(1)
{
    return vertices;
}

std::vector<Edge *> Clique::getEdges() const // Time complexity: O(1)
{
    return edges;
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

bool Clique::hasEdge(Edge *e) const // Time complexity: O(1)
{
    try
    {
        edgesMap.at(std::make_pair(e->getV1()->getId(), e->getV2()->getId()));
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