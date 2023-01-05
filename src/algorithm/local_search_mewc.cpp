/**
 * @file local_search_mewc.cpp
 * @brief This file contains the implementation of the local search MEWC algorithm
 * @authors
 * - Valentin Hervé <valentinherve60@gmail.com>
 * @date 2022-12-30
 */

#include <iostream>
#include "mewc.hpp"
#include "../common.hpp"

void findMaxClique(Graph g){
    Clique clique;
    auto verticies = g.getVertices();

    for(auto vertex : verticies){
        std::cout << vertex->getId() << std::endl;
    }
}

Clique findInitialSolution(Graph g){
    UNUSED(g);
    // Au pif ou a un endroit avec des critère qui font qu'on va plus vite (genre au vertex qui a le plus de points par ex)
    return Clique();
}

Clique findNeighboor(Graph g){
    UNUSED(g);
    // Bwaaaaa comment on trouve un meilleur voisin :/
    return Clique();
}

Clique localSearchMEWC(Graph g)
{
    findMaxClique(g);

    // Find init solution
    // while(some stop condition) // Smg like "if no improvement log(n) times, then stop"
    //      visit neighboors of solution (not the already visited ones)
    //      if(better solution found)
    //          solution become the better one

    return Clique();
}