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

Clique findMaxClique(Graph g, VertexPtr init_vertex){ // add banned verticies ?
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

    return clique;

    // Pseudo-code

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

unsigned int improveClique(Graph g, Clique* clique, std::unordered_set<VertexPtr> banned_verticies){ // add banned verticies + added verticies to see wich one don't visit after
    if(clique->isEmpty()){
        return 0;
    }
    auto verticies = g.getVertices();
    auto v = *(clique->getVertices().begin());
    unsigned int weight_improvement = 0;
    VertexPtr improvement_vertex;

    for(auto vertex : verticies){
        if(clique->hasVertex(vertex) || banned_verticies.find(vertex) != banned_verticies.end()){
            continue;
        }
        if(g.hasEdge(v, vertex)){
            auto clique_verticies = clique->getVertices();
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
                for(auto clique_vertex : clique_verticies){
                    if(clique_vertex == vertex){
                        continue;
                    }
                    weight_improvement += g.getEdge(clique_vertex, vertex).value()->getWeight();
                }
                clique->addVertex(vertex);
                improvement_vertex = vertex;
                break;
            }
        }
        else{
            banned_verticies.insert(vertex); // If we have no edges between some verticies and the clique, we can ban them
        }
    }
    
    if(weight_improvement == 0){ // If I didn't improve the clique, stop recursivity
        cout << "not improved :/" << endl;
        return 0;
    }

    cout << "improved by adding vertex : " << improvement_vertex->getId() << " / weight bonus : " << weight_improvement << endl;
    return weight_improvement + improveClique(g, clique, banned_verticies); // If I improve, see if I can improve more
}

Clique findNeighboor(Graph g, Clique init_clique, std::unordered_set<VertexPtr>* tested_verticies){
    auto clique_verticies = init_clique.getVertices();
    unsigned int min_weight = clique_verticies.size() * 100; // edge weight is less than 100 so the weight of the edges of a vertex in the clique is less than 100 times the number of verticies in the clique
    VertexPtr min_weight_vertex = nullptr;
    for(auto clique_vertex : clique_verticies){
        if(tested_verticies->find(clique_vertex) != tested_verticies->end()){ // do not try 2 times the same improvement
            continue;
        }
        unsigned int weight = 0;
        for(auto clique_vertex2 : clique_verticies){
            if(clique_vertex == clique_vertex2){
                continue;
            }
            weight += g.getEdge(clique_vertex, clique_vertex2).value()->getWeight();
        }
        if(weight < min_weight){
            min_weight = weight;
            min_weight_vertex = clique_vertex;
        }
    }

    if(min_weight_vertex == nullptr){ // If no improvement, return the original clique
        cout << "No improvement found" << endl;
        return init_clique;
    }

    cout << "Min weight vertex in clique : " << min_weight_vertex->getId() << " / weight = " << min_weight << " / New clique verticies : ";

    Clique new_clique;
    for(auto clique_vertex : clique_verticies){
        if(clique_vertex == min_weight_vertex){
            continue;
        }
        new_clique.addVertex(clique_vertex);
        cout << clique_vertex->getId();
    }

    cout << endl;

    std::unordered_set<VertexPtr> banned_verticies;
    banned_verticies.insert(min_weight_vertex);
    unsigned int improvement = improveClique(g, &new_clique, banned_verticies);
    cout << "Total improvement : " << improvement << endl;

    // if no improvement
    if(improvement <= min_weight){
        tested_verticies->insert(min_weight_vertex);
        return init_clique;
    }

    cout << "Better found !" << endl;
    return new_clique;

    // Pseudo-code
    // -
    // Remove vertex with min neighboor in clique or min edges' weights
    // Look a all neighboors of a random vertex in clique
    // if one of them is connected to every one in clique
    //      see if the weights of its edges is better than the old one
    //      if yes
    //          add this vertex to the clique and see if we ca improve it
    //      else
    //          see if we can improve the clique and if the improvement is better than the old solution
}

Clique localSearchMEWC(Graph g)
{
    // Clique c = findMaxClique(g, g.getVertex(6).value());
    Clique clique;
    clique.addVertex(g.getVertex(8).value());
    clique.addVertex(g.getVertex(6).value());
    std::unordered_set<VertexPtr> tested_verticies; // do not try 2 times the same improvement
    for(int i = 0; i < 5; i++){
        clique = findNeighboor(g, clique, &tested_verticies);
    }

    cout << "\n\n------- Best solution found -------" << endl;
    auto cv = clique.getVertices();
    for(auto v : cv){
        cout << v->getId() << " ";
    }
    cout << endl;

    // Find init solution
    // while(some stop condition) // Smg like "if no improvement log(n) times, then stop"
    //      visit neighboors of solution (not the already visited ones)
    //      if(better solution found)
    //          solution become the better one

    return Clique();
}