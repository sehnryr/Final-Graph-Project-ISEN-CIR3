/**
 * @file grasp_mewc.cpp
 * @brief This file contains the implementation of the grasp MEWC algorithm
 * @authors
 *  Antoine ESNAULT <antoine.esnault@isen-ouest.yncrea.fr>
 * @date 2022-12-30
 */

#include <algorithm>

#include "mewc.hpp"
#include "../common.hpp"

/**
 * @brief Returns the vertices sorted by the sum of their edges weights
 *
 * @param graph The graph
 * @param vertices The vertices to consider
 * @param gamma The highest weight edge of the graph
 * @return std::vector<VertexPtr> The vertices sorted by the sum of their edges weights
 */
std::vector<VertexPtr> sortVerticesSumWeight(
    Graph graph,
    std::unordered_set<VertexPtr> vertices,  // O(n^2)
    int gamma
    ) 
{
    std::vector<std::pair<VertexPtr, long unsigned int>> weights;
    std::vector<VertexPtr> sortedVertices;
    unsigned int alpha = 0.5;                                       //Critère pour la RCL   

    // Allocate the vectors
    weights.reserve(vertices.size());
    sortedVertices.reserve(vertices.size());

    // Get the weights
    auto adjMatrix = graph.getAdjacencyMatrix();
    for (auto vertex : vertices)
    {
        long unsigned int weight = 0;
        auto neighbors = adjMatrix[vertex->getId()];
        for (const auto &[neighbor, edge] : neighbors)
        {
            weight += edge->getWeight();
        }
        if (weight < gamma/(1+alpha)){                                      // Critère pour la RCL
            weights.push_back(std::make_pair(vertex, weight));
        }
        
    }

    // Sort the vertices by weight
    std::sort(weights.begin(), weights.end(), [](const auto &a, const auto &b)
              { return a.second > b.second; });

    // Get the vertices
    for (const auto &[vertex, weight] : weights)
        sortedVertices.push_back(vertex);

    return sortedVertices;
}


/**
 * @brief MakeRCL
 */
void MakeRCL(Graph graph,std::unordered_set<VertexPtr> &RCL){
    unsigned int alpha = 0.5;                           // ?
    long unsigned int gamma = 0;                             // The best weight of edges in the graph


/*
*  To know gamma, we online need to use it once so we need to change it
*/
    auto adjMatrix = graph.getAdjacencyMatrix();        //Adjency Matrix to know which edge in the graph has the best weight
    std::unordered_set<VertexPtr> vertices = graph.getVertices();
    for (auto vertexLine : vertices)
    {
        for (auto vertexCol : vertices){
            auto neighbors = adjMatrix[vertexCol->getId()][vertexLine->getId()];
            if (neighbors->getWeight() > gamma)
            {
                gamma = neighbors->getWeight();
            }
        }
    }



}


/**
 * @brief Select a vertex inside the Restricted Candidate List randomly
 *
 * @param std::unordered_set<VertexPtr> RCL 
 * @return std::vector<VertexPtr> The vertex choose randomly
 */
VertexPtr SelectElementAtRandom(std::unordered_set<VertexPtr> &RCL){
    return;
}


/**
 * @brief Adapt the RCL 
 *
 * @param  
 * @return std::vector<VertexPtr> The vertices sorted by the sum of their edges weights
 */
void AdaptGreedyFunction(VertexPtr &s){

}


/**
 * @brief Construct a random clique of the graph  
 *
 * @param Cliques 
 * @return std::vector<VertexPtr> The vertices sorted by the sum of their edges weights
 */
void ConstructGreedyRandomizedSolution(Graph g,Clique &Solution){
    //boucle à ajouter
    std::unordered_set<VertexPtr> RCL = {};                     //Restricted Candidate List 
    MakeRCL(g,RCL);
    auto s = SelectElementAtRandom(RCL);
    Solution.addVertex(s);                  // Add Vertex to the solution we create
    AdaptGreedyFunction(s);
}


/**
 * @brief Compare the MEWC we find with our best MEWC
 *
 * @param Cliques 
 * @return std::vector<VertexPtr> The vertices sorted by the sum of their edges weights
 */
void LocalSearch(Clique s){

}

/**
 * @brief Compare the MEWC we find with our best MEWC
 *
 * @param Cliques 
 * @return std::vector<VertexPtr> The vertices sorted by the sum of their edges weights
 */
void UpdateBestSolution(Clique Sol,Clique BestSol){
    if (Sol.getWeight() > BestSol.getWeight())
    {
        BestSol = Sol;
    }
    
}

Clique graspMEWC(Graph g)
{
    UNUSED(g);
    Clique BestSolution;
    Clique Solution;
    // TODO : implement the grasp algorithm

    //While BestSolution change
    while (BestSolution.getWeight() == Solution.getWeight()){
        ConstructGreedyRandomizedSolution(g,Solution);
        LocalSearch(Solution);
        UpdateBestSolution(Solution,BestSolution);
    }
    
    return BestSolution;
}