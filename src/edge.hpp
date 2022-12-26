#ifndef EDGE_HPP
#define EDGE_HPP

class Vertex;

class Edge
{
public:
    Edge(Vertex *v1, Vertex *v2, int weight);
    ~Edge();
    Vertex *getV1() const;
    Vertex *getV2() const;
    int getWeight() const;

private:
    Vertex *v1;
    Vertex *v2;
    int weight;
};

#endif // EDGE_HPP