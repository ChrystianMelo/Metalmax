#include <cassert>
#include <queue>
#include <limits>

#include "Algorithms.h"

using GraphNodeHash = GraphNode::GraphNodeHash;
using GraphNodeEqual = GraphNode::GraphNodeEqual;

namespace {
	/**
	 * \brief Realiza uma BFS no grafo residual para encontrar um caminho de source até sink.
	 */
	bool bfsEdmondKarp(Graph* graph,
		GraphNode* source,
		GraphNode* sink,
		std::unordered_map<GraphNode*, GraphEdge*, GraphNodeHash, GraphNodeEqual>& parentEdge)
	{
		// "parentEdge" guardará, para cada nó, a aresta usada para chegar nele
		parentEdge.clear();

		// Marca nós visitados
		std::unordered_map<GraphNode*, bool, GraphNodeHash, GraphNodeEqual> visited;
		for (auto& node : graph->getNodes()) {
			visited[&node] = false;
		}

		// Fila para BFS
		std::queue<GraphNode*> queue;
		queue.push(source);
		visited[source] = true;

		// BFS
		while (!queue.empty()) {
			GraphNode* u = queue.front();
			queue.pop();

			// Percorre todas as arestas saindo de u
			for (GraphEdge& edge : u->getEdges()) {
				GraphNode* v = edge.getTarget();

				// Se ainda não visitado e há capacidade residual > 0
				if (!visited[v] && edge.getFlow() > 0) {
					// Registra a aresta usada para chegar em v
					parentEdge[v] = &edge;
					visited[v] = true;
					queue.push(v);

					// Se chegamos no sink, podemos parar a BFS
					if (*v == *sink) {
						return true;
					}
				}
			}
		}

		// Não foi possível chegar ao sink
		return false;
	}

}

std::pair<int, std::unordered_map<std::pair<int, int>, int, PairHash>> Algorithms::EdmondKarp(Graph* graph, GraphNode* source, GraphNode* sink)
{
	int maxFlow = 0;

	// parentEdge[v] = aresta usada para chegar em v na BFS
	std::unordered_map<GraphNode*, GraphEdge*, GraphNodeHash, GraphNodeEqual> parentEdge;

	// (Pending) Corrigir.
	std::unordered_map<std::pair<int, int>, int, PairHash> edgeFlow;

	// Enquanto existir caminho de aumento (augmenting path) da BFS
	while (bfsEdmondKarp(graph, source, sink, parentEdge)) {
		// Encontra a capacidade residual mínima ao longo do caminho encontrado
		int pathFlow = std::numeric_limits<int>::max();

		// 1) Percorrer o caminho do sink até source usando parentEdge
		GraphNode* curr = sink;
		while (*curr != *source) {
			GraphEdge* edge = parentEdge[curr];
			pathFlow = std::min(pathFlow, edge->getFlow());
			curr = edge->getSource();
		}

		// 2) Atualiza capacidades do grafo residual (arestas e reversas)
		curr = sink;
		while (*curr != *source) {
			GraphEdge* edge = parentEdge[curr];

			// Subtrair pathFlow da aresta no sentido direto
			edge->setFlow(edge->getFlow() - pathFlow);

			// Somar pathFlow na aresta reversa
			auto reverse = edge->getReverse();
			reverse->setFlow(reverse->getFlow() + pathFlow);

			curr = edge->getSource();
		}

		// Soma no fluxo total
		maxFlow += pathFlow;

		for (const auto& pair : parentEdge) {
			auto edge = pair.second;
			if (edge->getFlow() > 0) {
				std::pair<int, int> key = std::make_pair(edge->getSource()->getIndex(), edge->getTarget()->getIndex());
				edgeFlow[key] = edge->getFlow();
			}
		}
	}

	return std::make_pair<>(maxFlow, edgeFlow);
}