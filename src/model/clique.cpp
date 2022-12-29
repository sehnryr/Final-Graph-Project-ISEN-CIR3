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

void Clique::addVertex(std::shared_ptr<Vertex> v)
{
    if (!hasVertex(v))
    {
        vertices.push_back(v);
        verticesMap[v->getId()] = v;
    }
}

std::vector<std::shared_ptr<Vertex>> Clique::getVertices() const
{
    return vertices;
}

bool Clique::hasVertex(std::shared_ptr<Vertex> v) const // Time complexity: O(1)
{
    if (getVertex(v->getId()))
        return true;
    return false;
}

std::optional<std::shared_ptr<Vertex>> Clique::getVertex(unsigned int id) const // Time complexity: O(1)
{
    try
    {
        return verticesMap.at(id);
    }
    catch (const std::out_of_range &e)
    {
        UNUSED(e);
        return {};
    }
}

void Clique::setWeight(long unsigned int weight)
{
    this->weight = weight;
}

void Clique::addWeight(long unsigned int weight)
{
    this->weight += weight;
}

long unsigned int Clique::getWeight() const // Time complexity: O(n^2)
{
    return weight;
}

long unsigned int Clique::getSize() const
{
    return vertices.size();
}

bool Clique::isEmpty() const
{
    return vertices.empty();
}