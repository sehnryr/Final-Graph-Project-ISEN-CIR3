#include <unordered_set>
#include <vector>

#include "mewc.hpp"

/**
 * @brief Get the weight of a clique
 *
 * This function calculates the weight of a clique. If the clique is not a clique,
 * it returns an empty optional.
 *
 * The time complexity of this function is O(n^2), where n is the size of the clique.
 *
 * @param clique The clique to get the weight of
 * @return std::optional<long unsigned int> The weight of the clique, an empty optional
 * if the clique is not a clique
 */
std::optional<long unsigned int> getCliqueWeight(Graph graph, Clique clique)
{
    // variable to store the weight of the clique
    long unsigned int weight = 0;
    // get a set of all vertices in the clique
    std::unordered_set<VertexPtr> vertices = clique.getVertices();

    // iterate over all possible pairs of vertices in the clique
    for (auto v1 : vertices)
        for (auto v2 : vertices)
            // if the vertices are the same, continue
            if (v1 == v2)
                continue;
            // if the vertices are connected, add the weight of the edge
            // to the weight of the clique
            else if (auto edge = graph.getEdge(v1, v2))
                weight += edge.value()->getWeight();
            // if the vertices are not connected, the clique is not a clique
            else
                return {};

    // return the weight of the clique
    return weight;
}

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
    Graph graph,
    Clique &R,
    std::unordered_set<VertexPtr> &P,
    std::unordered_set<VertexPtr> &X,
    std::vector<Clique> &cliques,
    int depth = 0)
{
    // Base case : if P and X are empty, add the clique R to the vector of cliques
    if (P.empty() && X.empty())
        cliques.push_back(R);

    // Create a copy of P to iterate through
    std::unordered_set<VertexPtr> P_copy = P;

    // Recursive case : iterate through the vector of vertices in P
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
        BronKerbosch(graph, R_new, P_new, X_new, cliques, depth + 1);

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
Clique exactMEWC(Graph g)
{
    // variable to store the maximum weight clique
    Clique max_clique;

    // get all the maximal cliques in the graph
    Clique R;
    std::unordered_set<VertexPtr> P = g.getVertices();
    std::unordered_set<VertexPtr> X;
    std::vector<Clique> cliques;       // vector to store the maximal cliques
    BronKerbosch(g, R, P, X, cliques); // O(3^(n/3))

    // iterate over all maximal cliques
    for (auto clique : cliques) // O(3^(n/3))
    {
        // get the weight of the clique
        // note that it will always be a clique, because it is a maximal clique
        // and the Bron-Kerbosch algorithm only returns maximal cliques
        auto weight = getCliqueWeight(g, clique); // O(n^2)

        clique.setWeight(weight.value());
        // if the clique is a clique and has a higher weight than the current
        // maximum weight clique, set the maximum weight clique to the current clique
        if (weight && weight.value() > max_clique.getWeight())
            max_clique = clique;
    }

    // return the maximum clique
    return max_clique;
}