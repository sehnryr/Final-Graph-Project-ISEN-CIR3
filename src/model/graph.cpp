#include "graph.hpp"

Graph::Graph()
{
}

Graph::Graph(std::vector<Vertex *> vertices,
             std::vector<Edge *> edges)
{
    this->vertices = vertices;
    this->edges = edges;
}

Graph::~Graph()
{
    vertices.clear();
    edges.clear();
}

void Graph::addVertex(Vertex *v)
{
    vertices.push_back(v);
}

void Graph::addEdge(Edge *e)
{
    edges.push_back(e);
}

std::vector<Vertex *> Graph::getVertices() const
{
    return vertices;
}

std::vector<Edge *> Graph::getEdges() const
{
    return edges;
}