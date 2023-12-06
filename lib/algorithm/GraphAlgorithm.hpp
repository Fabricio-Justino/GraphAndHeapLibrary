//
// Created by Fabricio on 29/11/2023.
//

#ifndef GRAPHALGORITHM_GRAPHALGORITHM_HPP
#define GRAPHALGORITHM_GRAPHALGORITHM_HPP

#include "Graph.hpp"
#include <queue>
#include <stack>
#include <memory>
#include <numeric>
#include <limits>

#include "PairHeap.hpp"

template <class T>
class GraphAlgorithm {
private:

    Graph<T> *graph;
    std::unordered_map<T, Edge<T>> edgeTo;
    std::unordered_map<T, double> distTo;
    std::unordered_set<T> marked;
    PairHeap<T, double> minHeap;

    void clearDataStructure();
    bool contains(const std::unordered_map<T, Edge<T>> &map, const T &key);
    bool contains(const std::unordered_set<T> &set,const T &key);
    void relax(const Edge<T> &edge);

public:
    explicit GraphAlgorithm(Graph<T> *graph);
    void changeGraph(Graph<T> *graf);
    GraphAlgorithm<T> & depthFirstSearch(const T &seek);
    GraphAlgorithm<T> & breadthFirstSearch(const T &seek);
    GraphAlgorithm<T> & dijkstra(const T &init);
    bool hasPathTo(const T &seek);
    std::unique_ptr<std::stack<T>> pathTo(const T &to);
    double sourceDistTo(const T& seek);
    void prim(Graph<T> *graf, const T& source);
};

template<class T>
void GraphAlgorithm<T>::prim(Graph<T> *graf, const T& source) {
    if (graph->isEmpty() || (*graph)[source].empty()) return;

    clearDataStructure();

    const double INFINITY = std::numeric_limits<double>::infinity();
    for (const auto& vertex : graph->getVertices())
        distTo[vertex] = INFINITY;
}

template<class T>
double GraphAlgorithm<T>::sourceDistTo(const T &seek) {
    return this->distTo[seek];
}

template<class T>
bool GraphAlgorithm<T>::contains(const std::unordered_set<T> &set,const T &key) {
    return set.find(key) != set.end();
}

template<class T>
bool GraphAlgorithm<T>::contains(const std::unordered_map<T, Edge<T>> &map,const T &key) {
    return map.find(key) != map.end();
}

template<class T>
void GraphAlgorithm<T>::clearDataStructure() {
    this->marked.clear();
    this->edgeTo.clear();
    this->distTo.clear();
    this->minHeap.clear();
}

template<class T>
GraphAlgorithm<T>::GraphAlgorithm(Graph<T> *graph) {
    this->graph = graph;
    this->minHeap = PairHeap<T, double>::minPairHeap(minHeap);
}

template<class T>
void GraphAlgorithm<T>::changeGraph(Graph<T> *graf) {
    this->graph = graf;
}

template<class T>
GraphAlgorithm<T> & GraphAlgorithm<T>::depthFirstSearch(const T &seek) {
    if ((*this->graph)[seek].empty()) return *this;

    clearDataStructure();

    std::stack<T> nextGen;
    nextGen.push(seek);

    while (!nextGen.empty()) {
        const T current = nextGen.top();
        nextGen.pop();
        marked.insert(current);

        for (const auto &edge: (*graph)[current]) {
            if (!contains(marked, edge.getTo())) {
                nextGen.push(edge.getTo());

                edgeTo[edge.getTo()] = edge;
            }
        }
    }

    return *this;
}

template<class T>
GraphAlgorithm<T> &GraphAlgorithm<T>::breadthFirstSearch(const T &seek) {
    if ((*this->graph)[seek].empty()) return *this;
    clearDataStructure();

    std::queue<T> nextGen;
    nextGen.push(seek);

    while (!nextGen.empty()) {
        const T current = nextGen.front();
        nextGen.pop();
        marked.insert(current);

        for (const auto &edge: (*graph)[current]) {
            if (!contains(marked, edge.getTo())) {
                nextGen.push(edge.getTo());

                edgeTo[edge.getTo()] = edge;
            }
        }
    }

    return *this;
}

template<class T>
GraphAlgorithm<T> &GraphAlgorithm<T>::dijkstra(const T &init) {
    if (!contains(graph->getVertices(), init)) return *this;

    clearDataStructure();

    const double INFINITY = std::numeric_limits<double>::infinity();
    for (const auto &vertex : graph->getVertices()) {
        distTo[vertex] = INFINITY;
    }

    distTo[init] = 0;
    marked.insert(init);
    minHeap.add(init, 0);

    while (!minHeap.isEmpty()) {
        T current = minHeap.pool();
        for (const auto& edge : (*graph)[current]) {
            if (!contains(marked, edge.getTo())) {
                minHeap.add(edge.getTo(), edge.getWeight());
                marked.insert(edge.getTo());
                relax(edge);
            }
        }
    }
    
    return *this;
}

template <class T>
void GraphAlgorithm<T>::relax(const Edge<T> &edge) {
   if (distTo[edge.getFrom()] + edge.getWeight() < distTo[edge.getTo()]) {
       distTo[edge.getTo()] = distTo[edge.getFrom()] + edge.getWeight();
       edgeTo[edge.getTo()] = edge;
   }
}

template <typename T>
bool GraphAlgorithm<T>::hasPathTo(const T &seek) {
    return contains(marked, seek);
}

template<class T>
std::unique_ptr<std::stack<T>> GraphAlgorithm<T>::pathTo(const T &to) {
    auto paths = std::make_unique<std::stack<T>>();
    if (!hasPathTo(to)) {
        return paths;
    }
    
    T seek = to;
    while (edgeTo.find(seek) != edgeTo.end()) {
        paths->push(seek);
        seek = edgeTo[seek].getFrom();
    }
    paths->push(seek);
    return paths;
}

#endif //GRAPHALGORITHM_GRAPHALGORITHM_HPP
