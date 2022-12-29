#ifndef VERTEX_HPP
#define VERTEX_HPP

class Vertex
{
public:
    Vertex(unsigned int id);
    ~Vertex();
    unsigned int getId() const;

private:
    unsigned int id;
};

#endif // VERTEX_HPP