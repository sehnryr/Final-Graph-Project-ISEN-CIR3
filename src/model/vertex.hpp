/**
 * @file vertex.hpp
 * @brief Declaration of the Vertex class
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-26
 */

#include <memory>

#ifndef VERTEX_HPP
#define VERTEX_HPP

#define VertexPtr std::shared_ptr<Vertex>

/**
 * @brief The Vertex class
 *
 * This class represents a vertex in a graph. It contains the id of the vertex.
 */
class Vertex
{
public:
    Vertex(unsigned int id);
    ~Vertex();
    unsigned int getId() const;
    bool operator==(const Vertex &v) const;

private:
    unsigned int id;
};

#endif // VERTEX_HPP