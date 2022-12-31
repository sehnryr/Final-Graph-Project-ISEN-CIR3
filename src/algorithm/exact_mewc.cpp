#include "mewc.hpp"

/**
 * @brief Generates all possible subsets of vertices
 *
 * This function generates all possible subsets of vertices of size `size` from
 * the vector `vertices`. The subsets are generated recursively.
 *
 * The time complexity of this function is O(n^k), where n is the size of the
 * vector of vertices and k is the size of the subsets.
 * Worst case the time complexity is O(n^n).
 *
 * @param vertices The vector of vertices
 * @param vertices_subset The vector of vertices that will be used to generate
 * the subsets
 * @param size The size of the subsets
 * @param offset The offset of the vector of vertices
 * @return A vector of the possible subsets of vertices
 */
std::vector<std::vector<std::shared_ptr<Vertex>>> generateVerticesSubsets(
    std::vector<std::shared_ptr<Vertex>> vertices,
    std::vector<std::shared_ptr<Vertex>> &vertices_subset,
    long unsigned int size,
    long unsigned int offset = 0)
{
    // vector to store all subsets
    std::vector<std::vector<std::shared_ptr<Vertex>>> vertices_subsets;

    // Base case : if size is 0, add the current subset to the vector
    if (size == 0)
        vertices_subsets.push_back(vertices_subset);
    // Recursive case : iterate through the vector of vertices and generate all
    // possible subsets of size `size - 1`.
    else
        for (long unsigned int i = offset; i < vertices.size(); i++)
        {
            // Add the current vertex to the subset
            vertices_subset.push_back(vertices[i]);
            // Recursive call to generate subsets of size `size - 1`
            std::vector<std::vector<std::shared_ptr<Vertex>>> vertices_subsets_tmp =
                generateVerticesSubsets(vertices, vertices_subset, size - 1, i + 1);
            // Insert the subsets returned by the recursive call
            vertices_subsets.insert(
                vertices_subsets.end(),
                vertices_subsets_tmp.begin(),
                vertices_subsets_tmp.end());
            // Remove the current vertex from the subset to generate the next
            // subset
            vertices_subset.pop_back();
        }
    // Return all the subsets
    return vertices_subsets;
}

/**
 * @brief Finds the maximum weight clique in a graph using an exact algorithm
 *
 * This function finds the maximum weight clique in a graph by generating all
 * possible subsets of vertices and checking if they form a clique.
 *
 * The time complexity of this function is O(n * n^n * m), where n is the number
 * of vertices in the graph and m is the number of edges in the graph.
 *
 * @param g The graph
 * @return The maximum weight clique
 */
Clique exactMEWC(Graph g) // O(n * n^n * m)
{
    // variable to store the maximum weight clique
    Clique max_clique(g);
    // get all vertices in the graph
    std::vector<std::shared_ptr<Vertex>> vertices = g.getVertices();

    // iterate over the sizes of the subsets
    for (long unsigned int i = 1; i <= vertices.size(); i++) // O(n)
    {
        // dummy vector for the generateVerticesSubsets() function
        std::vector<std::shared_ptr<Vertex>> vertices_subset;
        // generate all subsets of size i
        std::vector<std::vector<std::shared_ptr<Vertex>>> vertices_subsets =
            generateVerticesSubsets(vertices, vertices_subset, i);

        // iterate over the subsets
        for (std::vector<std::shared_ptr<Vertex>> vertices_subset : vertices_subsets) // O(n^k)
        {
            // create a temporary clique to store the current subset
            Clique clique(g);
            // add all vertices in the subset to the clique
            for (auto vertex : vertices_subset) // O(k)
                clique.addVertex(vertex);

            // Check if the clique is a clique
            bool isClique = true;
            // nested loop to check all pairs of vertices in the subset
            for (long unsigned int i = 0; i < vertices_subset.size(); i++)
                for (long unsigned int j = i + 1; j < vertices_subset.size(); j++) // O(m)
                    // check if there is an edge between the vertices
                    if (auto edge = g.getEdge(vertices_subset[i], vertices_subset[j]))
                        // add the weight of the edge to the clique
                        clique.addWeight(edge.value()->getWeight());
                    else
                    {
                        // if there is no edge, the clique is not a clique
                        isClique = false;
                        break;
                    }
            // if the clique is not a clique, continue to the next subset
            if (!isClique)
                continue;
            // if the clique is a clique and has a greater weight than the
            // current maximum clique, update the maximum clique
            if (clique.getWeight() > max_clique.getWeight())
                max_clique = clique;
        }
    }
    // return the maximum clique
    return max_clique;
}