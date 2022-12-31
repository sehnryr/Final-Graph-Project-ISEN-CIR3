#ifndef VERTEX_HPP
#define VERTEX_HPP

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