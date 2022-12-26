#include <vector>

#ifndef VERTEX_HPP
#define VERTEX_HPP

class Vertex
{
public:
    Vertex(int id);
    ~Vertex();
    int getId() const;
    void addNeighbor(Vertex *v);
    std::vector<Vertex *> getNeighbors() const;
    bool hasNeighbor(Vertex *v) const;

private:
    int id;
    std::vector<Vertex *> neighbors;
};

#endif // VERTEX_HPP