/**
 * @file exact_mewc.cpp
 * @brief This file contains the implementation of the exact MEWC algorithm
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-30
 */

#include <vector>

#include "mewc.hpp"

/**
 * @brief Finds the maximal cliques in a graph using the Bron-Kerbosch algorithm
 *
 * This function finds all maximal cliques in a graph using the Bron-Kerbosch
 * algorithm. The algorithm is implemented recursively.
 *
 * The time complexity of this function is O(3^(n/3)), where n is the number of
 * vertices in the graph.
 * (https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm)
 *
 * @param g The graph to find the maximal cliques in
 * @param R The current clique
 * @param P The set of vertices that are adjacent to the current clique
 * @param X The set of vertices that are not adjacent to the current clique
 * @param cliques The vector of cliques to add the maximal cliques to
 */
void BronKerbosch(
    const Graph &graph,
    Clique &R,
    std::unordered_set<VertexPtr> &P,
    std::unordered_set<VertexPtr> &X,
    std::vector<Clique> &cliques)
{
    // Base case : if P and X are empty, add the clique R to the vector of cliques
    if (P.empty() && X.empty())
        cliques.push_back(R);
    // If only P is empty, backtrack
    if (P.empty())
        return;

    // Chose a pivot vertex from P
    // (Technically it would be from P U X but since if P is empty, we backtrack,
    // we can just chose a vertex from P. And, normally we would have a condition
    // on the choice of the pivot vertex but it would induce additional complexity
    // that isn't worth it.)
    VertexPtr pivot = *P.begin();

    // Create a copy of P without the neighbors of the pivot vertex
    std::unordered_set<VertexPtr> P_copy;
    for (auto v : P)
        if (!graph.hasEdge(v, pivot))
            P_copy.insert(v);

    // Recursive case : iterate through the vector of vertices in the copy of P
    for (auto v : P_copy)
    {
        // Create a new clique with the current vertex
        Clique R_new = R;
        R_new.addVertex(v);

        // Create a new vector of vertices for the recursive call with the
        // vertices in P that are adjacent to the current vertex
        std::unordered_set<VertexPtr> P_new;
        for (auto w : P)
            if (graph.getEdge(v, w))
                P_new.insert(w);

        // Create a new vector of vertices for the recursive call with the
        // vertices in X that are adjacent to the current vertex
        std::unordered_set<VertexPtr> X_new;
        for (auto w : X)
            if (graph.getEdge(v, w))
                X_new.insert(w);

        // Recursive call
        BronKerbosch(graph, R_new, P_new, X_new, cliques);

        // Remove the current vertex from P and add it to X
        P.erase(v);
        X.insert(v);
    }
}

/**
 * @brief Finds the maximum weight clique in a graph using an exact algorithm
 *
 * This function finds the maximum weight clique in a graph by generating all
 * possible subsets of vertices and checking if they form a clique.
 *
 * The time complexity of this function is O(3^(n/3) * n^2), where n is the number
 * of vertices in the graph.
 *
 * @param g The graph
 * @return The maximum weight clique
 */
Clique exactMEWC(const Graph &g)
{
    // variable to store the maximum weight clique
    Clique max_clique;

    // get all the maximal cliques in the graph
    Clique R;
    std::unordered_set<VertexPtr> P = g.vertices();
    std::unordered_set<VertexPtr> X;
    std::vector<Clique> cliques;       // vector to store the maximal cliques
    BronKerbosch(g, R, P, X, cliques); // O(3^(n/3))

    // iterate over all maximal cliques
    for (auto clique : cliques) // O(3^(n/3))
    {
        // if the clique is a clique and has a higher weight than the current
        // maximum weight clique, set the maximum weight clique to the current clique
        if (clique.weight(g) > max_clique.weight(g))
            max_clique = clique;
    }

    // return the maximum clique
    return max_clique;
}