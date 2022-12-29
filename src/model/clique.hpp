#include <map>
#include <memory>
#include <optional>
#include <vector>

#include "graph.hpp"
#include "edge.hpp"
#include "vertex.hpp"

#ifndef CLIQUE_HPP
#define CLIQUE_HPP

class Clique
{
public:
    Clique();
    ~Clique();
    void addVertex(std::shared_ptr<Vertex> v);
    std::vector<std::shared_ptr<Vertex>> getVertices() const;
    bool hasVertex(std::shared_ptr<Vertex> v) const;
    std::optional<std::shared_ptr<Vertex>> getVertex(unsigned int id) const;
    void setWeight(long unsigned int weight);
    void addWeight(long unsigned int weight);
    long unsigned int getWeight() const;
    long unsigned int getSize() const;

private:
    std::map<unsigned int, std::shared_ptr<Vertex>> verticesMap;
    std::vector<std::shared_ptr<Vertex>> vertices;
    long unsigned int weight;
};

#endif // CLIQUE_HPP