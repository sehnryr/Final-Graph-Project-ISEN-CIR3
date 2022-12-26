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

void Vertex::addEdge(Edge *e)
{
    edges.push_back(e);
}

std::vector<Edge *> Vertex::getEdges() const
{
    return edges;
}

std::vector<Vertex *> Vertex::getNeighbors() const
{
    std::vector<Vertex *> neighbors;
    for (auto e : edges)
    {
        if (e->getV1() == this)
            neighbors.push_back(e->getV2());
        else
            neighbors.push_back(e->getV1());
    }
    return neighbors;
}

bool Vertex::hasNeighbor(Vertex *v) const
{
    if (v == this)
        return false;

    for (auto e : edges)
        if (e->getV1() == v || e->getV2() == v)
            return true;
    return false;
}