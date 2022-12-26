#include "vertex.hpp"

Vertex::Vertex(int id)
{
    this->id = id;
}

Vertex::~Vertex()
{
}

int Vertex::getId() const
{
    return id;
}

void Vertex::addNeighbor(Vertex *v)
{
    neighbors.push_back(v);
}

std::vector<Vertex *> Vertex::getNeighbors() const
{
    return neighbors;
}

bool Vertex::hasNeighbor(Vertex *v) const
{
    for (auto &neighbor : neighbors)
        if (neighbor == v)
            return true;
    return false;
}