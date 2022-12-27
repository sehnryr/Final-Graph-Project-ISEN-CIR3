#include <iostream>

#include "graph.hpp"
#include "../common.hpp"

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

void Graph::addVertex(Vertex *v) // Time complexity: O(1)
{
    // If the vertex already exists, do nothing
    if (hasVertex(v))
        return;

    verticesMap[v->getId()] = v;
    vertices.push_back(v);
}

void Graph::addEdge(Edge *e) // Time complexity: O(1)
{
    // Considering simple graphs (no parallel edges and no self-loops)
    // If the edge already exists, do nothing
    if (hasEdge(e))
        return;

    edgesMap[std::make_pair(e->getV1()->getId(), e->getV2()->getId())] = e;
    edges.push_back(e);
}

std::vector<Vertex *> Graph::getVertices() const // Time complexity: O(1)
{
    return vertices;
}

std::vector<Edge *> Graph::getEdges() const // Time complexity: O(1)
{
    return edges;
}

bool Graph::hasVertex(Vertex *v) const // Time complexity: O(1)
{
    try
    {
        verticesMap.at(v->getId());
        return true;
    }
    catch (const std::out_of_range &e)
    {
        UNUSED(e);
        return false;
    }
}

bool Graph::hasEdge(Edge *e) const // Time complexity: O(1)
{
    try
    {
        edgesMap.at(std::make_pair(e->getV1()->getId(), e->getV2()->getId()));
        return true;
    }
    catch (const std::out_of_range &e)
    {
        UNUSED(e);
        return false;
    }
}