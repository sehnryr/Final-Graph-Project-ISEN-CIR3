/**
 * @file local_search_mewc.cpp
 * @brief This file contains the implementation of the local search MEWC algorithm
 * @authors
 * - Valentin Hervé <valentinherve60@gmail.com>
 * @date 2022-12-30
 */

#include "mewc.hpp"

using namespace std;

/**
 * @brief Improve the given set of vertices to find a maximal clique.
 *
 * This function is recursive and it takes a set of vertices and finds a maximal clique based on them.
 * If the weight of the new clique is less than the previous one, it returns
 * the original one.
 *
 * The time complexity of this function is O(n^3), where n is the number of
 * vertices in the graph: this function is called maximum n times and its complexity without recursivity is O(n²).
 *
 * @param g The graph to find the maximal clique in
 * @param clique The clique that may be improved
 * @param banned_vertices The set of vertices that cannot be in the max clique
 * @param min_weight The minimum weight improveùent that needs to be done
 * @param actual_weight_improvement The actual improvement in weight that has been made since this function was first called
 * @return The weight improvement if the clique has been improved, 0 otherwise
 */
unsigned int improveClique(
    Graph g,
    Clique *clique,
    std::unordered_set<VertexPtr> banned_vertices = std::unordered_set<VertexPtr>(),
    unsigned int min_weight = 0,
    unsigned int actual_weight_improvement = 0)
{
    if (clique->empty())
        return 0;

    // Copy the initial clique
    Clique clique2;
    auto cv = clique->vertices();
    for (auto clique_vertex : cv) // O(n)
        clique2.addVertex(clique_vertex);

    auto vertices = g.vertices();
    auto v = *(clique->vertices().begin());    // a random vertex in the clique
    unsigned int weight_improvement = 0;       // the weight improvement that can be done to this clique by adding a vertex in this iteration
    unsigned int total_weight_improvement = 0; // the weight_improvement by adding a vertex in this iteration + the other that comes after
    VertexPtr improvement_vertex = nullptr;    // the vertex that improves the weight of the clique

    // Try to find a vertex which is not in the clique but
    // which has all the vertices of the clique as neighbours
    for (auto vertex : vertices) // O(n^2)
    {
        // If the vertex is in the clique or banned, continue
        if (clique->hasVertex(vertex) || banned_vertices.find(vertex) != banned_vertices.end())
            continue;

        // If we have an edge between the vertex and the random vertex of the clique
        if (g.hasEdge(v, vertex))
        {
            auto clique_vertices = clique->vertices();
            bool valid = true;

            // See if the vertex is adjacent to all vertices of the clique
            for (auto clique_vertex : clique_vertices) // O(n)
            {
                if (vertex->id() == clique_vertex->id())
                    continue;

                // If we don't have an edge between the vertex and one of the clique
                if (!g.hasEdge(clique_vertex, vertex))
                    valid = false;
            }
            // If valid = true, all vertices in the clique are adjacent of the vertex
            if (valid)
            {
                // Calculated the weight improvement when adding this vertex to the clique
                for (auto clique_vertex : clique_vertices) // O(n)
                {
                    if (clique_vertex == vertex)
                        continue;

                    weight_improvement += g.getEdge(clique_vertex, vertex).value()->weight();
                }
                clique2.addVertex(vertex);

                // See if we can improve more the clique
                total_weight_improvement = weight_improvement + improveClique(
                                                                    g,
                                                                    &clique2,
                                                                    banned_vertices,
                                                                    min_weight,
                                                                    actual_weight_improvement + weight_improvement); // Called maximum n times

                // If we are not better than the old solution, return 0
                if (total_weight_improvement + actual_weight_improvement <= min_weight)
                {
                    return 0;
                }
                else
                {
                    // The clique has been improved, so we replace the original one by the improved one
                    *clique = clique2;

                    return total_weight_improvement;
                }
            }
        }
        else
        {
            // If we have no edges between some vertices and the clique, we can ban them
            banned_vertices.insert(vertex);
        }
    }

    // If we didn't improve the clique, stop recursivity
    return 0;
}

/**
 * @brief Find a first solution to start with.
 *
 * This function finds a first maximal clique. The vertices of this clique are chosen by
 * first taking the one with the highest degree, its best degree neighbour and then the
 * maximum clique is found by calling 'improveClique()'.
 *
 * The time complexity of this function is O(n^3), where n is the number of
 * vertices in the graph.
 *
 * @param g The graph to find the maximal clique in
 * @return The maximal clique found
 */
Clique findInitialSolution(Graph g)
{
    if (g.vertices().size() < 2)
        return Clique();

    auto adjacency_matrix = g.adjacencyMatrix();
    unsigned int max_degree = 0;                                     // the maximum vertex degree in the graph
    unsigned int max_vertex = 0;                                     // the vertex of maximum degree in the graph
    std::unordered_map<unsigned int, unsigned int> vertices_degrees; // the degrees of all vertices

    // For all vertices
    for (unsigned int i = 1; i <= adjacency_matrix.size(); i++) // O(n)
    {
        // the degree of the vertex i
        auto degree = adjacency_matrix[i].size();
        vertices_degrees[i] = degree;

        // If the degree of this vertex is better than the actual max degree
        // modify the max degree and the max vertex
        if (degree > max_degree)
        {
            max_degree = degree;
            max_vertex = i;
        }
    }

    auto vertices = g.vertices();
    unsigned int max_degree2 = 0; // the second maximum vertex degree in the graph
    unsigned int max_vertex2 = 0; // the second vertex of maximum degree in the graph

    // For all vertices as candidates
    for (auto vertex : vertices) // O(n)
    {
        if (vertex->id() == max_vertex)
            continue;

        // If I have an edge between the max vertex and the candidate
        if (g.hasEdge(vertex->id(), max_vertex))
        {
            // If the degree of the candidate is higher than the max degree, replace it
            if (vertices_degrees[vertex->id()] > max_degree2)
            {
                max_degree2 = vertices_degrees[vertex->id()];
                max_vertex2 = vertex->id();
            }
        }
    }

    // Create a clique with the vertex of max degree and its neighbour of max degree
    Clique clique;
    clique.addVertex(g.getVertex(max_vertex).value());
    clique.addVertex(g.getVertex(max_vertex2).value());

    // Get a full clique based on these two vertices
    improveClique(g, &clique, std::unordered_set<VertexPtr>(), 0, 0); // O(n^3)

    return clique;
}

/**
 * @brief Try to find a better clique weight by removing a vertex.
 *
 * This function removes the minimum weight vertex from the clique and tries to find
 * a maximal clique based on this new set of vertices.
 *
 * The time complexity of this function is O(n^3), where n is the number of
 * vertices in the graph.
 *
 * @param g The graph to find the maximal clique in
 * @param init_clique The clique that may be improved
 * @param tested_vertices The set of vertices that will not be tested
 * @return The max clique found by removing the vertex if it is better, the original one otherwise
 */
Clique findNeighbor(Graph g, Clique init_clique, std::unordered_set<VertexPtr> *tested_vertices)
{
    auto clique_vertices = init_clique.vertices();
    // minimum weight added by a vertex in the clique
    unsigned int min_weight = clique_vertices.size() * 101; // edge weight is less than 100 so the weight of the edges of a vertex in the clique is less than 101 times the number of vertices in the clique
    VertexPtr min_weight_vertex = nullptr;                  // vertex that adds the minimum weight in the clique

    // For all vertices in the clique
    for (auto clique_vertex : clique_vertices) // O(n²)
    {
        // If the vertex has already been tested, do not try it another time
        if (tested_vertices->find(clique_vertex) != tested_vertices->end())
            continue;

        unsigned int weight = 0; // weight added by this vertex in the clique

        // For all vertices in the clique
        for (auto clique_vertex2 : clique_vertices)
        {
            if (clique_vertex == clique_vertex2)
                continue;

            // Get the weight between the vertex and all its neighbours in the clique
            weight += g.getEdge(clique_vertex, clique_vertex2).value()->weight();
        }

        // If the weight added by this vertex is less than the current minimum, modify it
        if (weight < min_weight)
        {
            min_weight = weight;
            min_weight_vertex = clique_vertex;
        }
    }

    // If no improvements have been made, this means that all possibilities have been tested, so we return the original clique
    if (min_weight_vertex == nullptr)
        return init_clique;

    // If I have a vertex to remove, create a new clique which is a
    // copy of the original with the tested vertex removed
    Clique new_clique;
    for (auto clique_vertex : clique_vertices) // O(n)
    {
        if (clique_vertex == min_weight_vertex)
            continue;

        new_clique.addVertex(clique_vertex);
    }

    // Put the tested vertex as banned
    std::unordered_set<VertexPtr> banned_vertices;
    banned_vertices.insert(min_weight_vertex);
    unsigned int improvement = improveClique(g, &new_clique, banned_vertices, min_weight, 0); // O(n^3)

    // If no better solution have been found, return the original clique and put the tested vertex in tested_verticies
    if (improvement <= min_weight)
    {
        tested_vertices->insert(min_weight_vertex);
        return init_clique;
    }

    // If a better solution have been found, return this solution
    return new_clique;
}

/**
 * @brief Finds the maximum weight clique in a graph using a local search algorithm.
 *
 * This function seeks to find a maximum clique by taking an initial solution,
 * then looking at the neighbours of that solution and keeping only those that improve it.
 *
 * The time complexity of this function is O(n^5), where n is the number
 * of vertices in the graph.
 *
 * @param g The graph to find the maximal clique in
 * @return The maximum weight clique found by local search
 */
Clique localSearchMEWC(const Graph &g)
{
    Clique max_clique = findInitialSolution(g);    // The initial solution that may be improved ( O(n^3) )
    std::unordered_set<VertexPtr> tested_vertices; // The vertices that have been tested

    // As long as the break conditions have not been reached
    while (1) // n² times
    {
        unsigned int c_weight = max_clique.weight(g);                // The weight of the clique before modifying it
        unsigned int tested_vertices_size = tested_vertices.size(); // The size of the set of tested vertices

        // Try improving the clique weight by removing a vertex
        max_clique = findNeighbor(g, max_clique, &tested_vertices); // O(n^3)

        // If the weight of the clique is still the same, that means that it has not been improved
        if (max_clique.weight(g) == c_weight)
        {
            // If the size of the set of tested vertices is still the same, that means that we do not have any other vertex to try
            if (tested_vertices.size() == tested_vertices_size)
                break;
        }
        else
            // If a better solution have been found, we must try again every vertices that have already been removed
            tested_vertices = std::unordered_set<VertexPtr>();
    }

    return max_clique;
}