/**
 * @file clique.cpp
 * @brief Implementation of the Clique class
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-26
 */

#include "clique.hpp"
#include "../common.hpp"

/**
 * @brief Construct a new Clique:: Clique object
 */
Clique::Clique()
    : _weight(0), _modified(false)
{
}

/**
 * @brief Destroy the Clique:: Clique object
 */
Clique::~Clique()
{
}

/**
 * @brief Get the weight of the clique
 *
 * This function calculates the weight of a clique. If the clique is not a clique,
 * it returns 0.
 *
 * The time complexity of this function is O(n^2), where n is the size of the clique.
 *
 * @param Graph graph The graph in which the clique is
 * @return long unsigned int The weight of the clique
 */
long unsigned int Clique::weight(const Graph &graph)
{
    if (_modified && _vertices.size() > 1)
    {
        _weight = 0;
        auto _vertices = Graph::vertices();

        // iterate over all possible pairs of vertices in the clique
        for (auto it = _vertices.begin(); it != _vertices.end(); ++it)
            for (auto jt = it; jt != _vertices.end(); ++jt)
                // if the vertices are the same, continue
                if (it == jt)
                    continue;
                // if the vertices are connected, add the weight of the edge
                // to the weight of the clique
                else if (auto edge = graph.getEdge(*it, *jt))
                    _weight += edge.value()->weight();
                // if the vertices are not connected, the clique is not a clique
                else
                    return 0;
    }

    _modified = false;
    return _weight;
}