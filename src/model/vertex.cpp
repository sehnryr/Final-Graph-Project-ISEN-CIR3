#include <iostream>

#include "vertex.hpp"
#include "../common.hpp"

Vertex::Vertex(unsigned int id)
{
    this->id = id;
}

Vertex::~Vertex()
{
}

unsigned int Vertex::getId() const // Time complexity: O(1)
{
    return id;
}

void Vertex::addEdge(Edge *e) // Time complexity: O(1)
{
    // If the edge is not incident to this vertex, do nothing
    if (e->getV1() != this && e->getV2() != this)
        return;

    Vertex *neighbor = e->getV1() == this ? e->getV2() : e->getV1();
    if (hasNeighbor(neighbor))
        return;

    // Assuming that the graph is simple (no parallel edges and no self-loops)
    edgesMap[neighbor->getId()] = e;
    edges.push_back(e);
    neighbors.push_back(neighbor);
}

std::vector<Edge *> Vertex::getEdges() const // Time complexity: O(1)
{
    return edges;
}

std::vector<Vertex *> Vertex::getNeighbors() const // Time complexity: O(1)
{
    return neighbors;
}

bool Vertex::hasNeighbor(Vertex *v) const // Time complexity: O(1)
{
    try
    {
        edgesMap.at(v->getId());
        return true;
    }
    catch (const std::out_of_range &e)
    {
        UNUSED(e);
        return false;
    }
}