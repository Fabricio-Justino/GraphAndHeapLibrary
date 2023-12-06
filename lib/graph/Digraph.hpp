//
// Created by Fabricio on 29/11/2023.
//

#ifndef GRAPHALGORITHM_DIGRAPH_HPP
#define GRAPHALGORITHM_DIGRAPH_HPP

#include "Graph.hpp"
#include <ostream>

template <class T>
class Digraph : public Graph<T> {

public:
    bool removeVertex(const T &data) override;

    void addEdge(const T &from, const T &to, int weight) override;

public:
    friend std::ostream &operator<<(std::ostream &os, const Digraph<T> &digraph) {
        auto &graph = digraph.graph;
        for (const auto &[key, value]: graph) {
            if (!value.empty()) os << key << " -> ";
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
bool Digraph<T>::removeVertex(const T &data) {
    auto &graph = this->graph;
    this->vertices.erase(data);

    if (graph.find(data) != graph.end()) {
        for (auto &[from, edges] : graph) {
            if (from == data) continue;
            auto ed = Edge<T>(from, data, 0);
            graph[from].erase(ed);
            this->edges.erase(ed);
        }

        graph.erase(data);
        return true;
    }
    return false;
}

template<class T>
void Digraph<T>::addEdge(const T &from, const T &to, int weight) {
    this->edgeTo(from, to, weight);
}

#endif //GRAPHALGORITHM_DIGRAPH_HPP




