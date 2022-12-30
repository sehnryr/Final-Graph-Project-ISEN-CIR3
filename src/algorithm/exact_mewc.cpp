#include "mewc.hpp"
#include "../common.hpp"

std::vector<std::vector<std::shared_ptr<Vertex>>> generateVerticesSubsets(
    std::vector<std::shared_ptr<Vertex>> vertices,
    std::vector<std::shared_ptr<Vertex>> &vertices_subset,
    long unsigned int size,
    long unsigned int offset = 0)
{
    std::vector<std::vector<std::shared_ptr<Vertex>>> vertices_subsets;
    if (size == 0)
        vertices_subsets.push_back(vertices_subset);
    else
        for (long unsigned int i = offset; i < vertices.size(); i++)
        {
            vertices_subset.push_back(vertices[i]);
            std::vector<std::vector<std::shared_ptr<Vertex>>> vertices_subsets_tmp =
                generateVerticesSubsets(vertices, vertices_subset, size - 1, i + 1);
            vertices_subsets.insert(
                vertices_subsets.end(),
                vertices_subsets_tmp.begin(),
                vertices_subsets_tmp.end());
            vertices_subset.pop_back();
        }
    return vertices_subsets;
}

Clique exactMEWC(Graph g)
{
    Clique max_clique;
    std::vector<std::shared_ptr<Vertex>> vertices = g.getVertices();
    for (long unsigned int i = 1; i <= vertices.size(); i++)
    {
        std::vector<std::shared_ptr<Vertex>> vertices_subset; // Dummy vector
        std::vector<std::vector<std::shared_ptr<Vertex>>> vertices_subsets =
            generateVerticesSubsets(vertices, vertices_subset, i);
        for (std::vector<std::shared_ptr<Vertex>> vertices_subset : vertices_subsets)
        {
            Clique clique;
            for (auto vertex : vertices_subset)
                clique.addVertex(vertex);
            // Check if the clique is a clique
            bool isClique = true;
            for (long unsigned int i = 0; i < vertices_subset.size(); i++)
                for (long unsigned int j = i + 1; j < vertices_subset.size(); j++)
                    if (auto edge = g.getEdge(vertices_subset[i], vertices_subset[j]))
                        clique.addWeight(edge.value()->getWeight());
                    else
                    {
                        isClique = false;
                        break;
                    }
            if (!isClique)
                continue;
            if (clique.getWeight() > max_clique.getWeight())
                max_clique = clique;
        }
    }
    return max_clique;
}