#ifndef GRAPHALGORITHM_GRAPH_HPP
#define GRAPHALGORITHM_GRAPH_HPP


#include <iostream>
#include <sstream>
#include <fstream>

#include <unordered_map>
#include <unordered_set>
#include <set>

#include <algorithm>

#include "Edge.hpp"

/**
 * A class that's represents a graph and its connections (edges)
 *
 * @tparam T data type holder by vertex
 */
template<class T>
class Graph {
protected:
    std::unordered_map<T, std::unordered_set<Edge<T>>> graph;
    std::unordered_set<T> vertices;
    std::unordered_set<Edge<T>> edges;

    virtual void edgeTo(const T &from, const T &to, int weight);

public:
    // constructors and delete
    Graph();
    ~Graph();

    // insertions
    /**
     *@brief Add a new vertex to the graph if there isn't one with same hash and '==' (operator).
     *
     * @param from The vertex to be added in the graph
     */
    void addVertex(const T &from);

    /**
     * @brief Adds an edge from one vertex to another with a specified weight.
     *
     * @param from The origin vertex.
     * @param to The destination vertex linked from the origin (from)
     * @param weight The weight of the edge.
     */
    virtual void addEdge(const T &from, const T &to, int weight);

     // removal methods
     /**
      * @brief Remove a vertex and all edges associated with it.
      *
      * @param data The vertex to ne removed from graph.
      * @return True if the vertex is successfully removed, false otherwise.
      */
     virtual bool removeVertex(const T &data);

    // accessors
    /**
     * @brief Find all vertices adjacent to the given value
     *
     * @param data The vertex to be find
     * @return Read-only set with all adjacent of data
     */
    const std::unordered_set<Edge<T>> &getAdjacent(const T &data);

    /**
     * @brief Find all vertices adjacent to the given value
     *
     * @param findValue The vertex to be find
     * @return A read-only set with all adjacent of data
     */
    const std::unordered_set<Edge<T>> &operator[](const T &findValue);

    /**
     *
     * @return A read-only set containing all vertices in the graph
     */
    const std::unordered_set<T> &getVertices() const;

    /**
     *
     * @return an String to be plotted on  <a ref="https://dreampuf.github.io/GraphvizOnline/">graphviz</a>
     */
    std::string toDot();


    /**
    * @brief Get a read-only set containing edges in the graph.
    *  In an undirected graph, both (u, v) and (v, u) edges are included.
    * 
    * @return A read-only set containing edges in the graph.
    */
    const std::unordered_set<Edge<T>> &getEdges() const;

    /**
     * @return True if the graph contains at last one vertex, false otherwise 
     */
    bool isEmpty() const;

    // print
    friend std::ostream &operator<<(std::ostream &os, const Graph<T> &graf) {
        for (const auto &[key, value]: graf.graph) {
            if (!value.empty()) os << key << " - ";
            else os << key;

            for (const auto &edge: value) {
                os << edge.getWeight() << " " << edge.getTo() << " ";
            }
            os << '\n';
        }

        return os;
    }
};

template<class T>
bool Graph<T>::isEmpty() const {
    return this->graph.empty();
}

template<class T>
const std::unordered_set<Edge<T>> &Graph<T>::getEdges() const {
    return edges;
}

template<class T>
const std::unordered_set<T> &Graph<T>::getVertices() const {
    return this->vertices;
}

template<class T>
void Graph<T>::edgeTo(const T &from, const T &to, int weight) {
    Edge<T> ed1(from, to, weight);

    if (edges.find(ed1) == edges.end())
        edges.insert(ed1);

    if (graph.find(from) == graph.end()) {
        graph[from] = std::unordered_set<Edge<T>>();
        this->vertices.insert(from);
    }

    if (graph.find(to) == graph.end()) {
        graph[to] = std::unordered_set<Edge<T>>();
        this->vertices.insert(to);
    }



    if (edges.find(ed1) == edges.end())
        this->edges.insert(ed1);
    graph[from].insert(ed1);
}

template<class T>
Graph<T>::Graph() = default;

template<class T>
Graph<T>::~Graph() = default;

template<class T>
void Graph<T>::addVertex(const T &from) {
    if (graph.find(from) == graph.end()) {
        this->vertices.insert(from);
        graph[from] = std::unordered_set<Edge<T>>();
    }
}

template<class T>
void Graph<T>::addEdge(const T &from, const T &to, int weight) {
    edgeTo(from, to, weight);
    edgeTo(to, from, weight);
}


template<class T>
bool Graph<T>::removeVertex(const T &data) {
    auto it = graph.find(data);
    this->vertices.erase(data);

    if (it != graph.end()) {
        for (auto &edge: graph[data]) {
            const T &to = edge.getTo();
            auto ed = Edge<T>(to, data, 0);
            graph[to].erase(ed);
            edges.erase(ed);
        }

        graph.erase(data);
        return true;
    }
    return false;
}

template<class T>
const std::unordered_set<Edge<T>> &Graph<T>::getAdjacent(const T &data) {
    // Verificar se o vértice existe no grafo antes de retornar suas arestas
    auto it = graph.find(data);
    if (it != graph.end()) {
        return graph[data];
    } else {
        // Retornar um conjunto vazio se o vértice não existir
        static const std::unordered_set<Edge<T>> emptySet;
        return emptySet;
    }
}

template<class T>
const std::unordered_set<Edge<T>> &Graph<T>::operator[](const T &findValue) {
    return getAdjacent(findValue);
}

template<class T>
std::string Graph<T>::toDot() {
    std::ostringstream sb;
    sb << "graph {" << std::endl;
    sb << "\trankdir = LR;" << std::endl;
    sb << "\tnode [shape = circle];" << std::endl;
    for (const auto &[k, v] : graph) {
        for (auto it = v.begin(); it != v.end(); ++it) {
                sb << '\t' << k << " -- " << (*it).getTo() << " [label = " << (*it).getWeight() << "];" << std::endl;
        }
    }

    sb << "}" << std::endl;
    return sb.str();
}

#endif //GRAPHALGORITHM_GRAPH_HPP