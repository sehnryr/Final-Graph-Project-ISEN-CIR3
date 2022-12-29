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
