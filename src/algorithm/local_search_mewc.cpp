/**
 * @file local_search_mewc.cpp
 * @brief This file contains the implementation of the local search MEWC algorithm
 * @authors
 * - Valentin Hervé <valentinherve60@gmail.com>
 * @date 2022-12-30
 */

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "mewc.hpp"
#include "../common.hpp"

using namespace std;

std::vector<VertexPtr> sortVerticesByDegrees(Graph g){
    auto adjacency_matrix = g.getAdjacencyMatrix();
    std::vector<VertexPtr> sorted_vertices;
    std::unordered_map<VertexPtr, unsigned int> vertices_degrees;
    for(unsigned int i = 1; i <= adjacency_matrix.size(); i++){
        unsigned int degree = 0;
        for(unsigned int j = 1; j <= adjacency_matrix[i].size(); j++){
            if(adjacency_matrix[i][j] != nullptr){
                degree ++;
            }
        }
        vertices_degrees[g.getVertex(i).value()] = degree;
    }

    while(vertices_degrees.size() > 0){
        unsigned int max = 0;
        VertexPtr max_degree_vertex = nullptr;
        for(unsigned int i = 1; i <= adjacency_matrix.size(); i++){
            if(vertices_degrees.find(g.getVertex(i).value()) == vertices_degrees.end()){
                continue;
            }
            if(vertices_degrees[g.getVertex(i).value()] > max || max == 0){
                max = vertices_degrees[g.getVertex(i).value()];
                max_degree_vertex = g.getVertex(i).value();
            }
        }
        sorted_vertices.push_back(max_degree_vertex);
        vertices_degrees.erase(max_degree_vertex);
    }

    return sorted_vertices;
}

/*
std::unordered_set<VertexPtr> findCliqueNeighbors(Graph g, Clique clique, std::vector<VertexPtr> sorted_vertices, std::unordered_map<VertexPtr, unsigned int> vertices_degrees){
    std::unordered_set<VertexPtr> clique_neighbors;
    auto adjacency_matrix = g.getAdjacencyMatrix();
    for(unsigned int i = 1; i <= adjacency_matrix.size(); i++){
        if(clique.hasVertex(g.getVertex(i).value())){
            continue;
        }

        bool valid = true;
        for(auto vertex : clique.getVertices()){
            if(adjacency_matrix[i][vertex->getId()] == nullptr){
                valid = false;
            }
        }

        if(valid){
            unsigned int degree = 0; // this degree is the neighbors vertices of the clique common with this vertex
            for(unsigned int j = 1; j <= adjacency_matrix[i].size(); j++){
                if(adjacency_matrix[i][j] != nullptr && adjacency_matrix[max_vertex][j] != nullptr && adjacency_matrix[max_vertex2][j] != nullptr){
                    degree ++;
                }
            }
            clique_neighbors[g.getVertex(i).value()] = degree;
        }

        if(adjacency_matrix[max_vertex][i] != nullptr && adjacency_matrix[max_vertex2][i] != nullptr){
            unsigned int degree = 0; // this degree is the neighbors vertices of the clique common with this vertex
            for(unsigned int j = 1; j <= adjacency_matrix[i].size(); j++){
                if(adjacency_matrix[i][j] != nullptr && adjacency_matrix[max_vertex][j] != nullptr && adjacency_matrix[max_vertex2][j] != nullptr){
                    degree ++;
                }
            }
            clique_neighbors[g.getVertex(i).value()] = degree;
        }
    }

    for(auto vertex : g.getVertices()){
        if(clique_neighbors.find(vertex) == clique_neighbors.end()){
            continue;
        }


    }
}*/

unsigned int improveClique(Graph g, Clique* clique, std::vector<VertexPtr> sorted_vertices, std::unordered_set<VertexPtr> banned_vertices = std::unordered_set<VertexPtr>(), unsigned int min_weight = 0, unsigned int actual_weight_improvement = 0){
    if(clique->isEmpty()){
        return 0;
    }
    Clique clique2;
    auto cv = clique->getVertices();
    for(auto clique_vertex : cv){
        clique2.addVertex(clique_vertex);
    }
    clique2.setWeight(clique->getWeight());

    auto vertices = g.getVertices();
    auto v = *(clique->getVertices().begin());
    unsigned int weight_improvement = 0;
    unsigned int total_weight_improvement = 0;
    VertexPtr improvement_vertex = nullptr;

    for(auto vertex : vertices){
        if(clique->hasVertex(vertex) || banned_vertices.find(vertex) != banned_vertices.end()){
            continue;
        }
        if(g.hasEdge(v, vertex)){
            auto clique_vertices = clique->getVertices();
            bool valid = true;
            for(auto clique_vertex : clique_vertices){
                if(vertex->getId() == clique_vertex->getId()){
                    continue;
                }
                if(!g.hasEdge(clique_vertex, vertex)){
                    valid = false;
                }
            }

            if(valid){
                for(auto clique_vertex : clique_vertices){
                    if(clique_vertex == vertex){
                        continue;
                    }
                    weight_improvement += g.getEdge(clique_vertex, vertex).value()->getWeight();
                }
                clique2.addVertex(vertex);
                clique2.addWeight(weight_improvement);
                total_weight_improvement = weight_improvement + improveClique(g, &clique2, sorted_vertices, banned_vertices, min_weight, actual_weight_improvement + weight_improvement);
                if(total_weight_improvement + actual_weight_improvement <= min_weight){
                    weight_improvement = 0;

                    clique2 = Clique(); // remove added vertices in clique2 if I didn't find a better solution
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
            banned_vertices.insert(vertex); // If we have no edges between some vertices and the clique, we can ban them
        }
    }
    
    if(improvement_vertex == nullptr){ // If I didn't improve the clique, stop recursivity
        return 0;
    }

    *clique = clique2; // If I have improve my clique, replace the original one by the improved one

    // cout << "    -> Improved by adding vertex : " << improvement_vertex->getId() << " / weight bonus : " << weight_improvement << endl;
    
    return total_weight_improvement;
}

Clique findInitialSolution(Graph g, std::vector<VertexPtr> sorted_vertices){
    VertexPtr max_vertex = sorted_vertices[0];
    VertexPtr max_vertex2 = nullptr;

    // Take the second vertex with max degree
    for(auto vertex : sorted_vertices){
        if(vertex == max_vertex){
            continue;
        }
        if(g.hasEdge(vertex, max_vertex)){
            max_vertex2 = vertex;
            break;
        }
    }

    // Generate clique with those 2 vertices
    Clique clique;
    clique.addVertex(max_vertex);
    clique.addVertex(max_vertex2);
    clique.setWeight(g.getEdge(max_vertex, max_vertex2).value()->getWeight());

    improveClique(g, &clique, sorted_vertices);

    return clique;
}

Clique findNeighboor(Graph g, Clique init_clique, std::vector<std::vector<VertexPtr>>* tested_vertices_sets, std::vector<VertexPtr> sorted_vertices, unsigned int to_remove = 1){
    auto clique_vertices = init_clique.getVertices();
    std::vector<VertexPtr> vertices_to_remove;
    unsigned int removed_weight = 0;
    
    for(unsigned int i = 0; i < to_remove; i++){
        unsigned int min_weight = clique_vertices.size() * 101; // edge weight is less than 100 so the weight of the edges of a vertex in the clique is less than 100 times the number of vertices in the clique
        VertexPtr min_weight_vertex = nullptr;
        for(auto clique_vertex : clique_vertices){
            if(std::find(vertices_to_remove.begin(), vertices_to_remove.end(), clique_vertex) != vertices_to_remove.end()){ // do not try 2 times the same improvement
                continue;
            }
            for(auto tested_verticies_set : *tested_vertices_sets){
                if(tested_verticies_set[i] == clique_vertex || tested_verticies_set.size() == to_remove){  // tester avec n'importe quel ordre plutôt que l'ordre déjà donné // mettre des sets de vecteurs à try plutôt ?
                    continue;
                }
            }
            unsigned int weight = 0;
            for(auto clique_vertex2 : clique_vertices){
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
            return init_clique;
        }
        vertices_to_remove.push_back(min_weight_vertex);
        removed_weight += min_weight;
    }

    Clique new_clique;
    std::unordered_set<VertexPtr> banned_vertices;
    for(auto clique_vertex : clique_vertices){
        if(std::find(vertices_to_remove.begin(), vertices_to_remove.end(), clique_vertex) != vertices_to_remove.end()){ // do not put the removed vertices
            banned_vertices.insert(clique_vertex);
            continue;
        }
        new_clique.addVertex(clique_vertex);
    }
    new_clique.setWeight(init_clique.getWeight() - removed_weight);

    unsigned int improvement = improveClique(g, &new_clique, sorted_vertices, banned_vertices, removed_weight, 0);

    // if keep the removed vertex is better
    if(improvement <= removed_weight){
        tested_vertices_sets->push_back(vertices_to_remove);
        return init_clique;
    }

    return new_clique;

    // Pseudo-code
    // -
    // Remove vertex with min neighboor in clique or min edges' weights
    // Look a all neighbors of a random vertex in clique
    // if one of them is connected to every one in clique
    //      see if the weights of its edges is better than the old one
    //      if yes
    //          add this vertex to the clique and see if we ca improve it
    //      else
    //          see if we can improve the clique and if the improvement is better than the old solution
}

Clique localSearchMEWC(Graph g){
    std::unordered_map<VertexPtr, unsigned int> vertices_degrees;
    auto sorted_vertices = sortVerticesByDegrees(g);
    Clique max_clique = findInitialSolution(g, sorted_vertices);
    // unsigned int no_improvement_found = 0; // Count the number of try with no improvement found
    // unsigned int max_number_of_tries = g.getVertices().size() / 2; // After 5 no better solution found -> Say that the current solution is the best one
    std::vector<std::vector<VertexPtr>> tested_vertices_sets;
    unsigned int max_tries = max_clique.getSize() / 2;
    unsigned int vertices_to_remove = 1;

    while(vertices_to_remove < max_tries){
        unsigned int c_weight = max_clique.getWeight();
        unsigned int tested_vertices_size = tested_vertices_sets.size();
        max_clique = findNeighboor(g, max_clique, &tested_vertices_sets, sorted_vertices, vertices_to_remove);
        if(max_clique.getWeight() == c_weight){ // Means that we didn't improve
            if(tested_vertices_sets.size() == tested_vertices_size){ // Means that we don't have any other vertex to test
                break;
            }
            vertices_to_remove++;
        }
        else{
            tested_vertices_sets = std::vector<std::vector<VertexPtr>>();
            vertices_to_remove = 1;
            max_tries = max_clique.getSize() / 2;
        }
    }

    // Pseudo code
    // -
    // Find init solution
    // while(some stop condition) // Smg like "if no improvement log(n) times, then stop"
    //      visit neighbors of solution (not the already visited ones)
    //      if(better solution found)
    //          solution become the better one

    return max_clique;
}