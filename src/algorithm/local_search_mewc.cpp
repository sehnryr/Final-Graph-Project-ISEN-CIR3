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

using namespace std;

void findMaxClique(Graph g, VertexPtr init_vertex){ // add banned verticies ?
    Clique clique;
    clique.addVertex(init_vertex);
    auto verticies = g.getVertices();

    for(auto vertex : verticies){
        if(vertex->getId() == init_vertex->getId()){
            continue;
        }
        if(g.hasEdge(init_vertex, vertex)){
            auto clique_verticies = clique.getVertices();
            bool valid = true;
            for(auto clique_vertex : clique_verticies){
                if(vertex->getId() == clique_vertex->getId()){
                    continue;
                }
                if(!g.hasEdge(clique_vertex, vertex)){
                    valid = false;
                }
            }

            if(valid){
                clique.addVertex(vertex);
            }
        }
    }

    auto cv = clique.getVertices();
    cout << "Clique vertex found containing : " << init_vertex->getId() << endl;
    for(auto clique_vertex : cv){
        cout << clique_vertex->getId() << endl;
    }

    // Given a vertex
    // Get an edge of the vertex
    // while(I still have neighboors unvisited of my first vertex)
    //      get another edge and see if the vertex is connected to the other of the clique
    //      if I upgrade my clique
    //          add vertex to clique
    //          visit other edges of the first vertex
    //      else
    //          continue visiting other neighboors till the end
    // do I have a max clique ?
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
    findMaxClique(g, g.getVertex(6).value());

    // Find init solution
    // while(some stop condition) // Smg like "if no improvement log(n) times, then stop"
    //      visit neighboors of solution (not the already visited ones)
    //      if(better solution found)
    //          solution become the better one

    return Clique();
}