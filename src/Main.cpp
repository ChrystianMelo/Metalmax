#include <iostream>
#include <cassert>
#include <climits>
#include <limits>

#include "Graph.h"
#include "GraphNode.h"
#include "Algorithms.h"

template <typename T>
bool contains(const std::vector<T*>& v, T& valor) {
	for (const auto* elem : v) {
		if (*elem == valor) {
			return true;
		}
	}
	return false;
}
int main() {
	// Lendo o número de nós e arestas
	std::size_t v, e;
	std::cin >> v >> e;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Lendo os nós
	std::vector<GraphNode*> geradores;
	std::unordered_map<std::size_t, GraphNode*> indexNodes;

	for (std::size_t i = 0; i < v; i++) {
		std::size_t index, t;
		std::cin >> index >> t;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		assert(index > 0);

		indexNodes[index] = new GraphNode(index, static_cast<int>(t));
		if (t == 0)
			geradores.push_back(indexNodes[index]);
	}
	assert(!geradores.empty());

	// Lendo as arestas
	for (std::size_t i = 0; i < e; i++) {
		std::size_t src, trg, capacity;
		std::cin >> src >> trg >> capacity;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		indexNodes[src]->connect(indexNodes[trg], static_cast<int>(capacity));
	}

	// Criando o source e o sink
	GraphNode* source = new GraphNode(0);
	for (auto* gerador : geradores)
		source->connect(gerador, INT_MAX);

	GraphNode* sink = new GraphNode(v + 1);
	for (auto& pair : indexNodes)
		if (!contains(geradores, *pair.second))
			pair.second->connect(sink, pair.second->getDemand());

	// Montando o grafo
	std::vector<GraphNode*> nodes;
	nodes.push_back(source);
	for (auto& pair : indexNodes)
		nodes.push_back(pair.second);
	nodes.push_back(sink);

	Graph graph(nodes);

	// Executando Edmond-Karp
	int maxFlow = Algorithms::EdmondKarp(&graph, source, sink);
	std::cout << maxFlow << std::endl;

	// Calculando demanda não atendida
	int totalDemand = 0;
	for (GraphNode* node : graph.getNodes()) {
		if (node->getDemand() > 0)
			totalDemand += node->getDemand();
	}
	int unattendedEnergy = totalDemand - maxFlow;
	std::cout << unattendedEnergy << std::endl;

	// Calculando o fluxo total dos geradores
	int totalOutgoingFlow = 0;
	for (auto* gerador : geradores) {
		for (GraphEdge& edge : gerador->getEdges())
			totalOutgoingFlow += edge.getFlow();
	}
	std::cout << totalOutgoingFlow << std::endl;

	// Encontrando arestas críticas
	std::vector<GraphEdge> criticalEdges;
	for (GraphNode* node : graph.getNodes()) {
		for (GraphEdge& edge : node->getEdges()) {
			if (edge.getFlow() == edge.getCapacity()) {
				criticalEdges.push_back(edge);
			}
		}
	}

	std::cout << criticalEdges.size() << std::endl;
	for (GraphEdge& edge : criticalEdges) {
		std::cout << edge.getSource()->getIndex() << " "
			<< edge.getTarget()->getIndex() << " "
			<< edge.getCapacity() << std::endl;
	}

	// Liberando memória
	for (auto& pair : indexNodes)
		delete pair.second;
	delete source;
	delete sink;

	return 0;
}
