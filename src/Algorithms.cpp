#include <cassert>
#include <queue>
#include <limits>

#include "Algorithms.h"

using GraphNodeHash = GraphNode::GraphNodeHash;
using GraphNodeEqual = GraphNode::GraphNodeEqual;

namespace {
	/**
	 * \brief Realiza uma BFS no grafo residual para encontrar um caminho de source até sink.
	 *
	 * \details Este método utiliza a busca em largura (BFS) para explorar o grafo residual
	 *          e verificar se existe um caminho entre o nó de origem (`source`) e o nó de destino (`sink`).
	 *          O grafo residual é representado por `graph`, onde as capacidades residuais indicam
	 *          a quantidade de fluxo que ainda pode ser enviada pelas arestas.
	 *
	 * \param graph Ponteiro para o grafo residual.
	 * \param source Ponteiro para o nó de origem do caminho.
	 * \param sink Ponteiro para o nó de destino do caminho.
	 * \param parentEdge Ponteiro para uma tabela hash que armazena a aresta de entrada para cada nó
	 *                   no caminho encontrado. É usada para reconstruir o caminho ao término da BFS.
	 *
	 * \return Retorna `true` se um caminho de `source` até `sink` for encontrado, e `false` caso contrário.
	 *
	 * \complexidade O(V + E), onde V é o número de nós e E é o número de arestas no grafo.
	 *               A BFS percorre todas as arestas adjacentes a cada nó uma vez durante a execução.
	 */
	bool bfsEdmondKarp(Graph* graph,
		GraphNode* source,
		GraphNode* sink,
		std::unordered_map<GraphNode*, GraphEdge*, GraphNodeHash, GraphNodeEqual>* parentEdge)
	{
		parentEdge->clear();

		std::unordered_map<GraphNode*, bool, GraphNodeHash, GraphNodeEqual> visited;
		for (auto* node : graph->getNodes()) {
			visited[node] = false;
		}

		std::queue<GraphNode*> queue;
		queue.push(source);
		visited[source] = true;

		while (!queue.empty()) {
			GraphNode* u = queue.front();
			queue.pop();

			for (GraphEdge& edge : u->getEdges()) {
				GraphNode* v = edge.getTarget();

				if (!visited[v] && edge.getFlow() > 0) {
					(*parentEdge)[v] = &edge;
					visited[v] = true;
					queue.push(v);

					if (*v == *sink) {
						return true;
					}
				}
			}
		}

		return false;
	}

}

int Algorithms::EdmondKarp(Graph* graph, GraphNode* source, GraphNode* sink)
{
	int maxFlow = 0;

	std::unordered_map<GraphNode*, GraphEdge*, GraphNodeHash, GraphNodeEqual> parentEdge;

	while (bfsEdmondKarp(graph, source, sink, &parentEdge))
	{
		int pathFlow = std::numeric_limits<int>::max();

		GraphNode* curr = sink;
		while (*curr != *source) {
			GraphEdge* edge = parentEdge[curr];
			pathFlow = std::min(pathFlow, edge->getFlow());
			curr = edge->getSource();
		}

		curr = sink;
		while (*curr != *source) {
			GraphEdge* edge = parentEdge[curr];
			edge->setFlow(edge->getFlow() - pathFlow);
			edge->getReverse()->setFlow(edge->getReverse()->getFlow() + pathFlow);
			curr = edge->getSource();
		}

		maxFlow += pathFlow;
	}

	return maxFlow;
}
