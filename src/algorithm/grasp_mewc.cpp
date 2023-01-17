/**
 * @file grasp_mewc.cpp
 * @brief This file contains the implementation of the grasp MEWC algorithm
 * @authors
 *  Antoine ESNAULT <antoine.esnault@isen-ouest.yncrea.fr>
 * @date 2022-12-30
 */

// #include <algorithm>

#include "mewc.hpp"
#include "../common.hpp"

// /**
//  * @brief Returns the vertices sorted by the sum of their edges weights
//  *
//  * @param graph The graph
//  * @param vertices The vertices to consider
//  * @param gamma The highest weight edge of the graph
//  * @return std::vector<VertexPtr> The vertices sorted by the sum of their edges weights
//  */
// std::vector<VertexPtr> MakeRCL(
//     Graph graph,
//     std::unordered_set<VertexPtr> vertices,  // O(n^2)
//     long unsigned int gamma
//     ) 
// {
//     std::vector<VertexPtr> Vertices;
//     unsigned int alpha = 0.5;                                       //Critère pour la RCL   



//     // Get the weights
//     auto adjMatrix = graph.getAdjacencyMatrix();
//     for (auto vertex : vertices)
//     {
//         long unsigned int weight = 0;
//         auto neighbors = adjMatrix[vertex->getId()];
//         for (const auto &[neighbor, edge] : neighbors)
//         {
//             weight += edge->getWeight();
//         }
//         if (weight < gamma/(1+alpha)){                                      // Critère pour la RCL
//             Vertices.push_back(vertex);                                         // ajouter une condition si vertex est exclut ne pas prendre
//         }
        
//     }

//     return Vertices;
// }


// /**
//  * @brief Select a vertex inside the Restricted Candidate List randomly
//  *
//  * @param std::unordered_set<VertexPtr> RCL 
//  * @return std::vector<VertexPtr> The vertex choose randomly
//  */
// VertexPtr SelectElementAtRandom(std::unordered_set<VertexPtr> &RCL){
//     return;
// }


// /**
//  * @brief Adapt the RCL 
//  *
//  * @param  
//  * @return std::vector<VertexPtr> The vertices sorted by the sum of their edges weights
//  */
// void AdaptGreedyFunction(VertexPtr &s){

// }


// /**
//  * @brief Construct a random clique of the graph  
//  *
//  * @param Cliques 
//  * @return std::vector<VertexPtr> The vertices sorted by the sum of their edges weights
//  */
// void ConstructGreedyRandomizedSolution(Graph g,Clique &Solution){
//     //boucle à ajouter
//     long unsigned int gamma;                                    // ajouter une fonction de calcul de gamma
//     VertexPtr X;
//     std::unordered_set<VertexPtr> RCL = {};                     //Restricted Candidate List 
//     MakeRCL(g,RCL,gamma);
//     auto s = SelectElementAtRandom(RCL);
//     Solution.addVertex(s);                  // Add Vertex to the solution we create
//     AdaptGreedyFunction(s);                 // ajout des vertex a exclure 
// }


// /**
//  * @brief Compare the MEWC we find with our best MEWC
//  *
//  * @param Cliques 
//  * @return std::vector<VertexPtr> The vertices sorted by the sum of their edges weights
//  */
// void LocalSearch(Clique s){

// }

// /**
//  * @brief Compare the MEWC we find with our best MEWC
//  *
//  * @param Cliques 
//  * @return std::vector<VertexPtr> The vertices sorted by the sum of their edges weights
//  */
// void UpdateBestSolution(Clique Sol,Clique BestSol){
//     if (Sol.getWeight() > BestSol.getWeight())
//     {
//         BestSol = Sol;
//     }
    
// }

Clique graspMEWC(Graph g)
{
    UNUSED(g);
    Clique BestSolution;
    // Clique Solution;
    // TODO : implement the grasp algorithm

    // //While BestSolution change
    // while (BestSolution.getWeight() == Solution.getWeight()){
    //     ConstructGreedyRandomizedSolution(g,Solution);
    //     LocalSearch(Solution);
    //     UpdateBestSolution(Solution,BestSolution);
    // }
    
    return BestSolution;
}