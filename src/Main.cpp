#include <iostream>
#include <cassert>
#include <limits>
#include <climits>

#include "Algorithms.h"

int main() {
	// Lendo o numero de nodos e arestas
	std::size_t v, e;
	std::cin >> v >> e;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Lerndo os nodos.
	std::vector<GraphNode*> geradores;
	std::unordered_map<std::size_t, GraphNode> indexNodes;
	for (std::size_t i = 0; i < v; i++) {
		std::size_t index, t;

		std::cin >> index >> t;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		assert(index > 0);

		indexNodes[index] = GraphNode(index, t);
		if (t == 0)
			geradores.push_back(&indexNodes[index]);
	}
	assert(!geradores.empty());

	// Lerndo as arestas.
	for (std::size_t i = 0; i < e; i++) {
		std::size_t src, trg, capacity;

		std::cin >> src >> trg >> capacity;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		indexNodes[src].connect(&indexNodes[trg], capacity);
	}

	// Construidno o grafo.
	GraphNode source(0); // source
	for (auto* gerador : geradores)
		source.connect(gerador, INT_MAX);

	GraphNode sink(v + 1);  // sink
	for (auto& pair : indexNodes)
		if (!contains(geradores, pair.second))
			pair.second.connect(&sink, pair.second.getDemand());

	std::vector<GraphNode> nodes;
	nodes.push_back(source);
	for (auto& pair : indexNodes)
		nodes.push_back(pair.second);
	nodes.push_back(sink);

	Graph graph({ nodes });

	// Passo 1
	int maxFlow = Algorithms::EdmondKarp(&graph, &source, &sink);
	std::cout << maxFlow << std::endl;

	// Passo 2
	int totalDemand = 0;
	for (GraphNode node : graph.getNodes()) {
		if (node.getDemand() > 0) {
			totalDemand += node.getDemand();
		}
	}
	int unattendedEnergy = totalDemand - maxFlow;
	std::cout << unattendedEnergy << std::endl;

	// Passo 3
	int totalOutgoingFlow = 0;
	for (auto gerador : geradores)
		for (GraphEdge& edge : gerador->getEdges()) {
			totalOutgoingFlow += edge.getFlow();
		}
	std::cout << totalOutgoingFlow << std::endl;

	// Passo 4
	std::vector<GraphEdge> criticalEdges;

	// ...

	std::cout << criticalEdges.size() << std::endl;
	for (GraphEdge& edge : criticalEdges) {
		std::cout << edge.getSource()->getIndex() << " "
			<< edge.getTarget()->getIndex() << " "
			<< edge.getCapacity() << std::endl;
	}

	return 0;
}


