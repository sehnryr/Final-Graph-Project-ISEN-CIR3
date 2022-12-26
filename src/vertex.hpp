#ifndef VERTEX_HPP
#define VERTEX_HPP

class Vertex
{
public:
    Vertex(int id);
    ~Vertex();
    int getId() const;

private:
    int id;
};

#endif // VERTEX_HPP