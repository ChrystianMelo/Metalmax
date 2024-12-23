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

int Algorithms::EdmondKarp(Graph* graph, GraphNode* source, GraphNode* sink)
{
	int maxFlow = 0;

	// parentEdge[v] = aresta usada para chegar em v na BFS
	std::unordered_map<GraphNode*, GraphEdge*, GraphNodeHash, GraphNodeEqual> parentEdge;

	// Enquanto existir caminho de aumento...
	while (bfsEdmondKarp(graph, source, sink, parentEdge))
	{
		int pathFlow = std::numeric_limits<int>::max();

		// 1) Achar o gargalo (capacidade residual mínima) do caminho achado
		GraphNode* curr = sink;
		while (*curr != *source) {
			GraphEdge* edge = parentEdge[curr];
			pathFlow = std::min(pathFlow, edge->getFlow());  // edge->getFlow() = capacidade residual no sentido direto
			curr = edge->getSource();
		}

		// 2) Atualizar as capacidades residuais (aresta direta e reversa)
		curr = sink;
		while (*curr != *source) {
			GraphEdge* edge = parentEdge[curr];
			edge->setFlow(edge->getFlow() - pathFlow); // diminui capacidade residual direta
			edge->getReverse()->setFlow(edge->getReverse()->getFlow() + pathFlow);
			curr = edge->getSource();
		}

		// 3) Atualiza o fluxo total
		maxFlow += pathFlow;
	}

	return maxFlow;
}
