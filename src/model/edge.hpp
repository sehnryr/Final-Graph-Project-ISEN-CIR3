/**
 * @file edge.hpp
 * @brief Declaration of the Edge class
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2022-12-26
 */

#include <memory>
#include <optional>

#include "vertex.hpp"

#ifndef EDGE_HPP
#define EDGE_HPP

#define EdgePtr std::shared_ptr<Edge>

/**
 * @brief The Edge class
 *
 * This class represents an edge in a graph. It contains the two vertices that
 * are connected by the edge and the weight of the edge.
 */
class Edge
{
public:
    Edge(VertexPtr first, VertexPtr second, unsigned int weight);
    ~Edge();

    // Get methods
    inline VertexPtr first() const { return _first; }
    inline VertexPtr second() const { return _second; }
    inline unsigned int weight() const { return _weight; }
    inline std::optional<VertexPtr> getVertex(unsigned int id) const
    {
        if (_first->id() == id)
            return _first;
        if (_second->id() == id)
            return _second;
        return {};
    }
    inline std::optional<VertexPtr> otherVertex(unsigned int id) const
    {
        if (auto v = getVertex(id))
            return *v == _first ? _second : _first;
        return {};
    }
    inline std::optional<VertexPtr> otherVertex(VertexPtr v) const { return otherVertex(v->id()); }

    // Boolean methods
    inline bool operator==(const Edge &e) const { return _first == e._first && _second == e._second && _weight == e._weight; }
    inline bool operator<(const Edge &e) const { return _weight < e._weight; }

    inline bool hasVertex(unsigned int id) const { return getVertex(id).has_value(); }
    inline bool hasVertex(VertexPtr v) const { return hasVertex(v->id()); }

    inline bool isIncident(unsigned int id1, unsigned int id2) const
    {
        if (auto _second = otherVertex(id1))
            return _second.value()->id() == id2;
        return false;
    }
    inline bool isIncident(VertexPtr first, VertexPtr second) const { return isIncident(first->id(), second->id()); }
    inline bool isIncident(EdgePtr e) const { return isIncident(e->first(), e->second()); }

private:
    VertexPtr _first;
    VertexPtr _second;
    unsigned int _weight;
};

// Hash and equal functions for the Edge class and EdgePtr class
namespace std
{
    /**
     * @brief Hash function for the Edge class
     *
     * @param e The edge to hash
     * @return std::size_t The hash of the edge
     */
    template <>
    struct hash<Edge>
    {
        std::size_t operator()(const Edge &e) const
        {
            return hash<unsigned int>()(e.first()->id()) ^
                   hash<unsigned int>()(e.second()->id()) ^
                   hash<unsigned int>()(e.weight());
        }
    };

    /**
     * @brief Equal function for the Edge class
     *
     * @param e1 The first edge
     * @param e2 The second edge
     * @return true If the edges are equal
     */
    template <>
    struct equal_to<Edge>
    {
        bool operator()(const Edge &e1, const Edge &e2) const
        {
            return e1 == e2;
        }
    };

    /**
     * @brief Hash function for the EdgePtr class
     *
     * @param e The edge to hash
     * @return std::size_t The hash of the edge
     */
    template <>
    struct hash<EdgePtr>
    {
        std::size_t operator()(const EdgePtr &e) const
        {
            return hash<Edge>()(*e);
        }
    };

    /**
     * @brief Equal function for the EdgePtr class
     *
     * @param e1 The first edge
     * @param e2 The second edge
     * @return true If the edges are equal
     */
    template <>
    struct equal_to<EdgePtr>
    {
        bool operator()(const EdgePtr &e1, const EdgePtr &e2) const
        {
            return *e1 == *e2;
        }
    };
} // namespace std

#endif // EDGE_HPP