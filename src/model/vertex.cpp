#include "vertex.hpp"

/**
 * @brief Construct a new Vertex:: Vertex object
 *
 * @param id The id of the vertex
 */
Vertex::Vertex(unsigned int id)
{
    this->id = id;
}

/**
 * @brief Destroy the Vertex:: Vertex object
 */
Vertex::~Vertex()
{
}

/**
 * @brief Get the id of the vertex
 *
 * @return unsigned int The id of the vertex
 */
unsigned int Vertex::getId() const // Time complexity: O(1)
{
    return id;
}

/**
 * @brief Compare two vertices
 *
 * @param v The vertex to compare to
 * @return true If the vertices have the same id
 * @return false If the vertices have different ids
 */
bool Vertex::operator==(const Vertex &v) const
{
    return id == v.id;
}