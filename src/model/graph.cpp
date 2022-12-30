#include <iostream>

#include "graph.hpp"
#include "../common.hpp"

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::addVertex(std::shared_ptr<Vertex> v) // Time complexity: O(1)
{
    // If the vertex already exists, do nothing
    if (hasVertex(v))
        return;

    verticesMap[v->getId()] = v;
    vertices.push_back(v);
}

void Graph::addEdge(std::shared_ptr<Edge> e) // Time complexity: O(1)
{
    // If the edge already exists, do nothing
    if (hasEdge(e))
        return;

    edges.push_back(e);
    // Considering simple undirected graphs (no parallel edges and no self-loops)
    // we need to add the edge to the adjacency matrix in both directions
    adjacencyMatrix[e->getV1()->getId()][e->getV2()->getId()] = e;
    adjacencyMatrix[e->getV2()->getId()][e->getV1()->getId()] = e;
}

std::vector<std::shared_ptr<Vertex>> Graph::getVertices() const // Time complexity: O(1)
{
    return vertices;
}

std::vector<std::shared_ptr<Edge>> Graph::getEdges() const // Time complexity: O(1)
{
    return edges;
}

bool Graph::hasVertex(std::shared_ptr<Vertex> v) const // Time complexity: O(1)
{
    if (getVertex(v->getId()))
        return true;
    return false;
}

bool Graph::hasEdge(std::shared_ptr<Edge> e) const // Time complexity: O(1)
{
    if (getEdge(e->getV1(), e->getV2()))
        return true;
    return false;
}

std::optional<std::shared_ptr<Vertex>> Graph::getVertex(unsigned int id) const // Time complexity: O(1)
{
    try
    {
        return verticesMap.at(id);
    }
    catch (const std::out_of_range &e)
    {
        UNUSED(e);
        return {};
    }
}

std::optional<std::shared_ptr<Edge>> Graph::getEdge(std::shared_ptr<Vertex> v1,
                                                    std::shared_ptr<Vertex> v2) const // Time complexity: O(1)
{
    try
    {
        return adjacencyMatrix.at(v1->getId()).at(v2->getId());
    }
    catch (const std::out_of_range &e)
    {
        UNUSED(e);
        return {};
    }
}

std::map<unsigned int, std::map<unsigned int, std::shared_ptr<Edge>>> Graph::getAdjacencyMatrix() const // Time complexity: O(1)
{
    return adjacencyMatrix;
}