#include <iostream>
#include <cassert>

#include "Algorithms.h"

int main() {
	// Lendo o numero de nodos e arestas
	std::size_t v, e;
	std::cin >> v >> e;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Lerndo os nodos.
	std::size_t geradorIndex = 0;
	std::unordered_map<std::size_t, GraphNode> indexNodes;
	for (std::size_t i = 0; i < v; i++) {
		std::size_t index, t;

		std::cin >> index >> t;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		assert(index > 0);

		indexNodes[index] = GraphNode(index, t);
		if (t == 0)
			geradorIndex = index;
	}
	assert(geradorIndex != 0);

	// Lerndo as arestas.
	for (std::size_t i = 0; i < e; i++) {
		std::size_t src, trg, capacity;

		std::cin >> src >> trg >> capacity;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		indexNodes[src].connect(&indexNodes[trg], capacity);
	}

	// Construidno o grafo.
	GraphNode source(0); // source
	source.connect(&indexNodes[geradorIndex], INT_MAX);

	GraphNode sink(v + 1);  // sink
	for (auto& pair : indexNodes)
		if (pair.second != indexNodes[geradorIndex])
			pair.second.connect(&sink, pair.second.getDemand());

	std::vector<GraphNode> nodes;
	nodes.push_back(source);
	for (auto& pair : indexNodes)
		nodes.push_back(pair.second);
	nodes.push_back(sink);

	Graph graph({ nodes });

	// Passo 1
	auto data = Algorithms::EdmondKarp(&graph, &source, &sink);
	int maxFlow = data.first;
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
	for (GraphEdge& edge : indexNodes[geradorIndex].getEdges()) {
		totalOutgoingFlow += edge.getFlow();
	}
	std::cout << totalOutgoingFlow << std::endl;

	// Passo 4
	std::vector<GraphEdge> criticalEdges;
	for (auto& node : graph.getNodes())
		for (auto& edge : node.getEdges()) {
			auto key = std::make_pair(node.getIndex(), edge.getTarget()->getIndex());
			if (edge.getCapacity() == data.second[key])
				criticalEdges.push_back(edge);
		}


	std::cout << criticalEdges.size() << std::endl;

	for (GraphEdge& edge : criticalEdges) {
		std::cout << edge.getSource()->getIndex() << " "
			<< edge.getTarget()->getIndex() << " "
			<< edge.getCapacity() << std::endl;
	}

	return 0;
}

