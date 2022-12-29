#include "edge.hpp"

Edge::Edge(std::shared_ptr<Vertex> v1,
           std::shared_ptr<Vertex> v2,
           unsigned int weight)
{
    this->v1 = v1;
    this->v2 = v2;
    this->weight = weight;
}

Edge::~Edge()
{
}

std::shared_ptr<Vertex> Edge::getV1() const
{
    return v1;
}

std::shared_ptr<Vertex> Edge::getV2() const
{
    return v2;
}

std::optional<std::shared_ptr<Vertex>> Edge::hasVertex(std::shared_ptr<Vertex> v) const
{
    if (v1 == v)
        return v1;
    if (v2 == v)
        return v2;
    return {};
}

std::optional<std::shared_ptr<Vertex>> Edge::isIncident(std::shared_ptr<Edge> e) const
{
    if (auto v = hasVertex(e->getV1()))
        return *v;
    if (auto v = hasVertex(e->getV2()))
        return *v;
    return {};
}

unsigned int Edge::getWeight() const
{
    return weight;
}

bool Edge::operator==(const Edge &e) const
{
    return v1 == e.v1 && v2 == e.v2;
}