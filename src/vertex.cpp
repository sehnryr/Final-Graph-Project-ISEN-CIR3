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