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
    bool operator<(const Vertex &v) const;

private:
    unsigned int id;
};

// Hash and equal functions for the Vertex class and VertexPtr class
namespace std
{
    /**
     * @brief Hash function for the Vertex class
     *
     * @param v The vertex to hash
     * @return std::size_t The hash of the vertex
     */
    template <>
    struct hash<Vertex>
    {
        std::size_t operator()(const Vertex &v) const
        {
            return hash<unsigned int>()(v.getId());
        }
    };

    /**
     * @brief Equal function for the Vertex class
     *
     * @param v1 The first vertex
     * @param v2 The second vertex
     * @return true If the vertices are equal
     */
    template <>
    struct equal_to<Vertex>
    {
        bool operator()(const Vertex &v1, const Vertex &v2) const
        {
            return v1 == v2;
        }
    };

    /**
     * @brief Hash function for the VertexPtr class
     *
     * @param v The vertex pointer to hash
     * @return std::size_t The hash of the vertex pointer
     */
    template <>
    struct hash<VertexPtr>
    {
        std::size_t operator()(const VertexPtr &v) const
        {
            return hash<Vertex>()(*v);
        }
    };

    /**
     * @brief Equal function for the VertexPtr class
     *
     * @param v1 The first vertex pointer
     * @param v2 The second vertex pointer
     * @return true If the vertex pointers are equal
     */
    template <>
    struct equal_to<VertexPtr>
    {
        bool operator()(const VertexPtr &v1, const VertexPtr &v2) const
        {
            return equal_to<Vertex>()(*v1, *v2);
        }
    };
} // namespace std

#endif // VERTEX_HPP