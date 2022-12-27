#include "edge.hpp"

Edge::Edge(Vertex *v1, Vertex *v2, unsigned int weight)
{
    this->v1 = v1;
    this->v2 = v2;
    this->weight = weight;
}

Edge::~Edge()
{
}

Vertex *Edge::getV1() const
{
    return v1;
}

Vertex *Edge::getV2() const
{
    return v2;
}

std::optional<Vertex *> Edge::isIncident(Edge *e) const
{
    if (e->getV1() == v1 || e->getV1() == v2)
        return e->getV1();
    if (e->getV2() == v1 || e->getV2() == v2)
        return e->getV2();
    return {};
}

unsigned int Edge::getWeight() const
{
    return weight;
}