#include <iostream>

#include "Digraph.hpp"
#include "GraphAlgorithm.hpp"
#include "PairHeap.hpp"
#include <iostream>

using namespace std;

int main() {
    Graph<string> graph;
    GraphAlgorithm<string> graphAlgorithm(&graph);

    graph.addVertex("H");
    graph.addVertex("Hg");
    graph.addVertex("Ag");

    graph.addVertex("Ni");
    graph.addVertex("Na");
    graph.addVertex("Cl");

    graph.addEdge("H", "Hg", 5);
    graph.addEdge("H", "Ag", 10);
    graph.addEdge("Ag", "Ni", 3);
    graph.addEdge("Hg", "Ni", 5);
    graph.addEdge("Ni", "Na", 15);
    graph.addEdge("Ni", "Cl", 13);
    graph.addEdge("Ag", "Pl", 20);


   cout << graph.toDot() << endl;

    graphAlgorithm.breadthFirstSearch("H");
    cout << (graphAlgorithm.hasPathTo("Pl") ? "SIM" : "NÃO") << endl;

    auto path = graphAlgorithm.pathTo("Pl");
    while (!path->empty()) {
        string ac = path->top();
        path->pop();
        cout << ac << ", ";
    }
    cout << endl;
    auto *g = new Graph<string>();
    graphAlgorithm.prim(g, "H");

    cout << endl << g->toDot() << endl;
    return 0;
}
