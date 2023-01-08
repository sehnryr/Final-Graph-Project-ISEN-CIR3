/**
 * @file local_search_mewc.cpp
 * @brief This file contains the implementation of the local search MEWC algorithm
 * @authors
 * - Valentin Hervé <valentinherve60@gmail.com>
 * @date 2022-12-30
 */

#include <iostream>
#include <unordered_map>
#include "mewc.hpp"
#include "../common.hpp"

using namespace std;

Clique findMaxClique(Graph g, VertexPtr init_vertex){ // Delete this useless thing
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

unsigned int improveClique(Graph g, Clique* clique, std::unordered_set<VertexPtr> banned_verticies = std::unordered_set<VertexPtr>(), unsigned int min_weight = 0, unsigned int actual_weight_improvement = 0){
    if(clique->isEmpty()){
        return 0;
    }
    Clique clique2;
    auto cv = clique->getVertices();
    for(auto clique_vertex : cv){
        clique2.addVertex(clique_vertex);
    }
    clique2.setWeight(clique->getWeight());

    auto verticies = g.getVertices();
    auto v = *(clique->getVertices().begin());
    unsigned int weight_improvement = 0;
    unsigned int total_weight_improvement = 0;
    VertexPtr improvement_vertex = nullptr;

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
                clique2.addVertex(vertex);
                clique2.addWeight(weight_improvement);
                total_weight_improvement = weight_improvement + improveClique(g, &clique2, banned_verticies, min_weight, actual_weight_improvement + weight_improvement);
                if(total_weight_improvement + actual_weight_improvement <= min_weight){
                    weight_improvement = 0;

                    clique2 = Clique(); // remove added verticies in clique2 if I didn't find a better solution
                    for(auto clique_vertex : cv){
                        clique2.addVertex(clique_vertex);
                    }

                } // If I'm not better than the old solution, I keep looking for a better solution
                else{
                    improvement_vertex = vertex;
                    break;
                }
            }
        }
        else{
            banned_verticies.insert(vertex); // If we have no edges between some verticies and the clique, we can ban them
        }
    }
    
    if(improvement_vertex == nullptr){ // If I didn't improve the clique, stop recursivity
        return 0;
    }

    *clique = clique2; // If I have improve my clique, replace the original one by the improved one

    cout << "    -> Improved by adding vertex : " << improvement_vertex->getId() << " / weight bonus : " << weight_improvement << endl;
    
    return total_weight_improvement;
}

Clique findInitialSolution(Graph g){
    auto adjacency_matrix = g.getAdjacencyMatrix();
    unsigned int max_degree = 0;
    unsigned int max_vertex = 0;
    std::unordered_map<unsigned int, unsigned int> verticies_degrees;
    for(unsigned int i = 1; i <= adjacency_matrix.size(); i++){
        unsigned int degree = 0;
        for(unsigned int j = 1; j <= adjacency_matrix[i].size(); j++){
            if(adjacency_matrix[i][j] != nullptr){
                degree ++;
            }
        }
        verticies_degrees[i] = degree;
        if(degree > max_degree){
            max_degree = degree;
            max_vertex = i;
        }
        cout << "Degree of " << i  << " -> " << degree << endl;
    }

    cout << "MAX VERTEX -> " << max_vertex << endl;

    // if = 0

    auto verticies = g.getVertices();
    unsigned int max_degree2 = 0;
    unsigned int max_vertex2 = 0;
    for(auto vertex : verticies){
        if(vertex->getId() == max_vertex){
            continue;
        }
        if(g.hasEdge(vertex, g.getVertex(max_vertex).value())){
            if(verticies_degrees[vertex->getId()] > max_degree2){
                max_degree2 = verticies_degrees[vertex->getId()];
                max_vertex2 = vertex->getId();
            }
            cout << "Degree of " << vertex->getId() << " -> " << verticies_degrees[vertex->getId()] << endl;
        }
    }

    cout << "MAX VERTEX 2 -> " << max_vertex2 << endl;

    Clique clique;
    clique.addVertex(g.getVertex(max_vertex).value());
    clique.addVertex(g.getVertex(max_vertex2).value());
    clique.setWeight(g.getEdge(g.getVertex(max_vertex).value(), g.getVertex(max_vertex2).value()).value()->getWeight());

    improveClique(g, &clique, std::unordered_set<VertexPtr>(), 0, 0);

    return clique;
}

Clique findNeighboor(Graph g, Clique init_clique, std::unordered_set<VertexPtr>* tested_verticies){
    cout << endl;

    auto clique_verticies = init_clique.getVertices();
    unsigned int min_weight = clique_verticies.size() * 101; // edge weight is less than 100 so the weight of the edges of a vertex in the clique is less than 100 times the number of verticies in the clique
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

    cout << "Test by removing : " << min_weight_vertex->getId() << " / weight = " << min_weight << " / New clique verticies : ";

    Clique new_clique;
    for(auto clique_vertex : clique_verticies){
        if(clique_vertex == min_weight_vertex){
            continue;
        }
        new_clique.addVertex(clique_vertex);
        cout << clique_vertex->getId() << " ";
    }
    new_clique.setWeight(init_clique.getWeight() - min_weight);

    cout << endl;

    std::unordered_set<VertexPtr> banned_verticies;
    banned_verticies.insert(min_weight_vertex);
    unsigned int improvement = improveClique(g, &new_clique, banned_verticies, min_weight, 0);

    // cout << "------- Solution found : " << improvement << " / " << min_weight << " -------" << endl;
    // auto cv = new_clique.getVertices();
    // for(auto v : cv){
    //     cout << v->getId() << " ";
    // }
    // cout << endl;

    // if keep the removed vertex is better
    if(improvement <= min_weight){
        cout << "  => No better solution found" << endl;
        tested_verticies->insert(min_weight_vertex);
        return init_clique;
    }

    cout << "  => Better solution found!" << endl;
    cout << "  => Improvement : " << improvement << " / " << min_weight << endl;

    // cout << "Better found !" << endl;
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
    // Clique clique;
    // clique.addVertex(g.getVertex(6).value());
    // clique.addVertex(g.getVertex(8).value());
    // std::unordered_set<VertexPtr> tested_verticies; // do not try 2 times the same improvement
    // for(int i = 0; i < 5; i++){
    //     clique = findNeighboor(g, clique, &tested_verticies);
    // }

    // cout << "\n\n------- Best solution found -------" << endl;
    // auto cv = clique.getVertices();
    // for(auto v : cv){
    //     cout << v->getId() << " ";
    // }
    // cout << endl;

    Clique max_clique = findInitialSolution(g);
    unsigned int no_improvement_found = 0; // Count the number of try with no improvement found
    unsigned int max_number_of_tries = 5; // After 5 no better solution found -> Say that the current solution is the best one
    std::unordered_set<VertexPtr> tested_verticies;

    while(no_improvement_found < max_number_of_tries){
        unsigned int c_weight = max_clique.getWeight();
        unsigned int tested_verticies_size = tested_verticies.size();
        max_clique = findNeighboor(g, max_clique, &tested_verticies);
        if(max_clique.getWeight() == c_weight){ // Means that we didn't improve
            if(tested_verticies.size() == tested_verticies_size){ // Means that we don't have any other vertex to test
                break;
            }
            no_improvement_found++;
        }
        else{
            tested_verticies = std::unordered_set<VertexPtr>();
            no_improvement_found = 0;
        }
    }

    auto cv = max_clique.getVertices();
    for(auto v : cv){
        cout << v->getId() << " ";
    }
    cout << endl;
    cout << "WEIGHT : " << max_clique.getWeight() << endl;


    // Find init solution
    // while(some stop condition) // Smg like "if no improvement log(n) times, then stop"
    //      visit neighboors of solution (not the already visited ones)
    //      if(better solution found)
    //          solution become the better one

    return max_clique;
}