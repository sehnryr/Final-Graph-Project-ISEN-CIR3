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
VertexPtr getFirstVertex(Graph graph)
{
    VertexPtr BestVertex;
    auto NumberOfNeighbors = 0;
    auto MaxNumberOfNeighbors = 0;
    auto adjMatrix = graph.getAdjacencyMatrix();
    auto vertices = graph.getVertices();

    for (int i = 0; i < vertices.size(); i++)
    {
        auto neighbors = adjMatrix[vertices[i].getId()];
        if(neighbors.size() > MaxNumberOfNeighbors)
        {
            MaxNumberOfNeighbors = neighbors.size();
            BestVertex = vertices[i].getId();
        }
    }

    return BestVertex;
    // bon j'ai plein d'erreur mais y'a l'idée je crois
}

// Modifie P de sorte à ce qu'il possède la liste des sommets candidats à notre clique pour la première itération (en gros tout les voisins du vertex choisi)
void getPotentielCandidate(Graph graph, VertexPtr &vertex, Clique &R, std::unordered_set<VertexPtr> &P)
{
    // Par example sur notre instance, on va avoir P = {2,3,4}

    auto adjMatrix = graph.getAdjacencyMatrix(); // transforme le graph en matrice adjacente
    auto neighbors = adjMatrix[vertex->getId()]; // recupere les neighbors

    auto i = neighbors.begin(); // debut de la liste
    while(i != neighbors.end()) // TANT QUE je n'ai pas parcouru toute la liste
    {
        // std::cout << *it << std::endl;
        P.insert(*i); // j'ajoute les voisins à P
        i++;
    }
}

// Modifie P de sorte à ce qu'il possède la liste des sommets candidats à notre clique (en gros tout les voisins du vertex choisi)
void updatePotentielCandidate(Graph graph, VertexPtr &vertex, std::unordered_set<VertexPtr> &P, Clique &R)
{
    // Par exemple, si notre vertex c'est 2, et qu'il a comme voisin (1,4), on doit obtenir P = {1,2,4} et donc supprimer 3

    auto adjMatrix = graph.getAdjacencyMatrix();
    auto neighbors = adjMatrix[vertex->getId()];

    for (auto i = P.begin(); i != P.end(); ) {
        if (neighbors.count(*i) == 0) 
        {
            // L'élément n'est pas dans neighbors, on le supprime de P
            i = P.erase(i);
        } else if(vertex = *i)
        {
            // L'élement est déjà dans R, on le supprime de P
            i = P.erase(i);
        }
        else
        {
            i++;
        }
        
    }   
        
}


// Modifie R en y ajoutant le voisin avec l'edge au plus haut poids entre les deux, Modifie TotalWeight pour ajouter le poids de l'edge entre le vertex et
void updateClique(Graph graph, VertexPtr &vertex, std::unordered_set<VertexPtr> &P, Clique &R)
{
    long unsigned int weight = 0; // variable temporaire correspond au poids de l'edge entre notre vertex et ses voisins
    long unsigned int BestWeight = 0; // variable correspondant au poids maximales obtenu lors de la lecture des voisins
    VertexPtr BestVertex; // meilleur voisin en gros
    long unsigned int CliqueWeight = 0;

    // je cherche le voisin avec le plus de poids
    auto i = P.begin();
    while(i != P.end())
    {
        if (vertex == *i)
        {
            i++;
            continue;
        }
        else
        {
            auto edge = graph.getEdge(vertex, *i);
            weight = edge.value()->getWeight();
            if(weight > BestWeight)
            {
                BestWeight = weight;
                VertexPtr BestVertex = *i;
                weight = 0;
            }
            else
            {
                weight = 0;
            }
        }
    }

    // je recupere le poids des edges entre les membres de ma clique et le membre que j'vais ajouté (le voisin au plus haut poids du dernier vertex de R)
    auto vertices = R.getVertices();
    for(auto v1 : vertices) // mm méthode que Youn en gros
    {
        auto edge = graph.getEdge(v1, BestVertex); // recupere le poids de l'edge entre de tout les membres de R et BestVertex
        CliqueWeight += edge.value()->getWeight(); // ajoute ce poids à une variable qui va etre ajouté aux poids total de la clique
    }

    R.addVertex(BestVertex);
    R.addWeight(CliqueWeight);
}


Clique constructiveMEWC(Graph g)
{
    UNUSED(g);
    // TODO : implement the constructive algorithm

    Clique R; //  clique qui forme la solution
    std::unordered_set<VertexPtr> P; // Liste de sommets candidats

    VertexPtr vertice;

    auto FirstVertex = getFirstVertex(g); // vertex avec le plus grand nombre de sommets

    R.addVertex(FirstVertex); // On ajoute le vertex à notre clique
    getPotentielCandidate(g, FirstVertex, R, P); // On recupère les neighbors de FirstVertex et on les mets dans P
    // imaginons l'instance
    // 4 4
    // 1 3 3
    // 1 2 6
    // 1 4 4
    // 2 4 5
    // Ici, on va avoir P = {2,3,4}

    while (P.size() != 0) // le but de mon algo va de réduire tout les candidats possible à 0, il n'y aura aucun autre candidats ajoutable à la clique
    {
        vertice = (R.getVertices()).end();
        updateClique(g, vertice, P, R); // (R.getVertices()).end() correspond à FirstVertex (dernier element de la clique)
        // j'ajoute le neighbors au plus haut poids à ma clique et j'ajoute son poids au poids de la clique
        vertice = (R.getVertices()).end();
        updatePotentielCandidate(g, vertice, P, R); // je recupere dernier element de la clique ajouté (celui qui a été ajouté par updateClique) et j'vais actualisé P
    }

    return R;
}
