#ifndef EDGE_HPP
#define EDGE_HPP

class Vertex;

class Edge
{
public:
    Edge(Vertex *v1, Vertex *v2, unsigned int weight);
    ~Edge();
    Vertex *getV1() const;
    Vertex *getV2() const;
    unsigned int getWeight() const;

private:
    Vertex *v1;
    Vertex *v2;
    unsigned int weight;
};

#endif // EDGE_HPP