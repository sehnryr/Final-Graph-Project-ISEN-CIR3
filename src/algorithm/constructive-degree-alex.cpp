/**
 * @file constructive_mewc.cpp
 * @brief This file contains the implementation of the constructive MEWC algorithm
 * @authors 
 * - Alexandre AUGUSTE <alexandre.auguste@isen-ouest.yncrea.fr> / Martin LOBEL <martin.lobel@isen-ouest.yncrea.fr>
 * @date 2022-12-30
 */

#include "mewc.hpp"
#include "../common.hpp"

// fonction qui retourne le vertex possédant le plus de voisin
VertexPtr getFirstVertexDegreeAlex(Graph graph)
{
    VertexPtr bestVertex;
    auto adjMatrix = graph.getAdjacencyMatrix();
    auto vertices = graph.getVertices();

    auto weight = 0;
    auto totalWeight = 0;
    auto bestWeight = 0;

    long unsigned int maxNumNeighbors = 0;

    for (auto vertex : vertices) // je verifie le nombre de voisins et l'ajoute dans MaxNumberOfNeighors et BestVertex si c'est le plus grand encore jamais atteint
    {
        auto neighbors = adjMatrix[vertex->getId()];
        if(neighbors.size() > maxNumNeighbors)
        {
            totalWeight = 0;
            maxNumNeighbors = neighbors.size();
            bestVertex = vertex;
            for (const auto& [neighbor, sharededge] : neighbors) 
            {
                weight = sharededge->getWeight();
                totalWeight += weight;
                weight = 0;
            }
            bestWeight = totalWeight;
        }
        else if(neighbors.size() == maxNumNeighbors)
        {
            totalWeight = 0;
            for (const auto& [neighbor, sharededge] : neighbors) 
            {
                weight = sharededge->getWeight();
                totalWeight += weight;
                weight = 0;
            }
            if(totalWeight > bestWeight)
            {
                bestWeight = totalWeight;
                bestVertex = vertex;
            }
        }
    }

    // for (auto vertex : vertices) // je verifie le poids des segments de tous les vertex et l'ajoute à bestVertex si c'est le plus grand jamais atteint, en cas d'égalité => ajoute au sommet du plus haut degré
    // {
    //     totalWeight = 0;
    //     auto neighbors = adjMatrix[vertex->getId()];
    //     for (const auto& [neighbor, sharededge] : neighbors) 
    //     {
    //         weight = sharededge->getWeight();
    //         totalWeight += weight;
    //         weight = 0;
    //     }

    //     if(totalWeight > bestWeight)
    //     {
    //         bestWeight = totalWeight;
    //         bestVertex = vertex;
    //         maxNumNeighbors = neighbors.size();
    //     }
    //     else if(totalWeight == bestWeight)
    //     {
    //         if(neighbors.size() > maxNumNeighbors)
    //         {
    //             bestVertex = vertex;
    //             maxNumNeighbors = neighbors.size();
    //         }
    //     }   
    // }

    return bestVertex;
}

// Modifie P de sorte à ce qu'il possède la liste des sommets candidats à notre clique pour la première itération (en gros tout les voisins du vertex choisi)
void getPotentielCandidateDegreeAlex(Graph graph, VertexPtr &vertex, std::unordered_set<VertexPtr> &P)
{
    // Par example sur notre instance, on va avoir P = {2,3,4}

    auto adjMatrix = graph.getAdjacencyMatrix(); // transforme le graph en matrice adjacente
    auto neighbors = adjMatrix[vertex->getId()]; // recupere les neighbors

    for (const auto& [neighbor, sharededge] : neighbors) // J'ajoute les voisins dans P
    // O(n)
    {
        VertexPtr vertexNeighbor = std::make_shared<Vertex>(neighbor);
        P.insert(vertexNeighbor);   
    }  
     
}

// Modifie P de sorte à ce qu'il possède la liste des sommets candidats à notre clique (en gros tout les voisins du vertex choisi)
void updatePotentielCandidateDegreeAlex(Graph graph, VertexPtr &vertex, std::unordered_set<VertexPtr> &P)
{
    // Par exemple, si notre vertex c'est 2, et qu'il a comme voisin (1,4), on doit obtenir P = {1,2,4} et donc supprimer 3

    auto adjMatrix = graph.getAdjacencyMatrix();
    auto neighbors = adjMatrix[vertex->getId()];
    std::unordered_set<VertexPtr> voisin; // unordered set des voisins vide

    for (const auto& [neighbor, sharededge] : neighbors) // on remplit le unordered set
    // O(n)
    {
        VertexPtr vertexNeighbor = std::make_shared<Vertex>(neighbor);
        voisin.insert(vertexNeighbor);   
    }

    for (auto i = P.begin(); i != P.end(); ) // O(n)
    {
        if (voisin.count(*i) == 0) // S'il n'y a pas l'element de P dans les voisins du dernier vertex choisi
        // O(1)
        {
            // L'élément n'est pas dans neighbors, on le supprime de P
            i = P.erase(i); // O(1)
        } else if(vertex == *i) // Si l'élement est déjà dans R
        {
            // L'élement est déjà dans R, on le supprime de P
            i = P.erase(i); // O(1)
        }
        else
        {
            i++;
        }        
    }   
        
}


// Modifie R en y ajoutant le voisin avec l'edge au plus haut poids entre les deux, Modifie TotalWeight pour ajouter le poids de l'edge entre le vertex et le voisin avec l'edge au plus haut poids. En cas d'égalité, prend l'edge au plus haut poids
void updateCliqueDegreeAlex(Graph graph, VertexPtr &vertex, std::unordered_set<VertexPtr> &P, Clique &S)
{
    long unsigned int weight = 0; // variable temporaire correspond au poids de l'edge entre notre vertex et ses voisins
    long unsigned int bestWeight = 0; // variable correspondant au poids maximales obtenu lors de la lecture des voisins
    VertexPtr bestVertex; // meilleur voisin en gros
    long unsigned int cliqueWeight = 0;
    long unsigned int maxNumNeighbors = 0;
    auto adjMatrix = graph.getAdjacencyMatrix();

    // je cherche le voisin avec le plus de poids
    auto i = P.begin();
    while(i != P.end()) // O(n)
    {
        if (vertex == *i) // Si le vertex choisi dans P est le mm que le vertex
        {
            i++;
            continue;
        }
        else // Ici je vais recupere l'edge entre le dernier vertex de mon unordered set et les vertex présent dans P, jusqu'a verifier qui possède le meilleur poids
        {
            auto edge = graph.getEdge(vertex, *i);
            weight = edge.value()->getWeight();
            auto neighbors = adjMatrix[(*i)->getId()]; // (*(*i)).getId();
            if(weight > bestWeight)
            {
                bestWeight = weight;
                bestVertex = *i;
                weight = 0;
                maxNumNeighbors = neighbors.size();
                i++;
            }
            else if(weight == bestWeight)
            {
                if(neighbors.size() > maxNumNeighbors)
                {
                    maxNumNeighbors = neighbors.size();
                    bestVertex = *i;
                }
                i++;
            }
            else
            {
                weight = 0;
                i++;
            }
        }
    }

    // je recupere le poids des edges entre les membres de ma clique et le membre que j'vais ajouté (le voisin au plus haut poids du dernier vertex de R)
    auto vertices = S.getVertices();
    for(auto v1 : vertices) // mm méthode que Youn en gros
    {
        auto edge = graph.getEdge(v1, bestVertex); // recupere le poids de l'edge entre de tout les membres de R et BestVertex
        cliqueWeight += edge.value()->getWeight(); // ajoute ce poids à une variable qui va etre ajouté aux poids total de la clique
    }

    S.addVertex(bestVertex);
    vertex = bestVertex;
    S.addWeight(cliqueWeight);
}

void constructiveMEWCRecursiveDegreeAlex(Graph G, VertexPtr &vertex, std::unordered_set<VertexPtr> &P, Clique &S)
{
    if(P.size() == 0)
    {
        return;
    }

    updateCliqueDegreeAlex(G, vertex, P, S);
    updatePotentielCandidateDegreeAlex(G, vertex, P);
    constructiveMEWCRecursiveDegreeAlex(G, vertex, P, S);
}

Clique constructiveMEWCDegreeAlex(Graph g)
{
    // UNUSED(g);
    // TODO : implement the constructive algorithm

    Clique S; //  clique qui forme la solution
    std::unordered_set<VertexPtr> P; // Liste de sommets candidats

    auto firstVertex = getFirstVertexDegreeAlex(g); // vertex avec le plus grand nombre de sommets
    VertexPtr lastvertex = firstVertex;

    S.addVertex(firstVertex); // On ajoute le vertex à notre clique
    getPotentielCandidateDegreeAlex(g, firstVertex, P); // On recupère les neighbors de FirstVertex et on les mets dans P
    // imaginons l'instance
    // 4 4
    // 1 3 3
    // 1 2 6
    // 1 4 4
    // 2 4 5
    // Ici, on va avoir P = {2,3,4}

    constructiveMEWCRecursiveDegreeAlex(g, lastvertex, P, S);

    return S;
}