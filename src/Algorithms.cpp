#include <cassert>
#include <limits> 

#include "Algorithms.h"
#include <unordered_set>

namespace {
	/**
	 * \brief
	 */
	class NullNodeVisitor : public NodeVisitor {
	public:
		void visit(GraphNode* node) override {
		}
	};

	/**
	 * \brief
	 */
	class SCCNodeVisitor : public NodeVisitor {
	public:
		SCCNodeVisitor()
			: m_sccs(), scc_(), prevNode_(nullptr) {}

		void visit(GraphNode* node) override {
			if (prevNode_ != nullptr && !prevNode_->isConnected(node)) {
				m_sccs.push_back(scc_);
				scc_ = SCC();
			}
			scc_.push_back(*node);
			prevNode_ = node;
		}

		void finalize() {
			if (!scc_.empty()) {
				m_sccs.push_back(scc_);
			}
		}

		std::vector<SCC> getSCCS() { return m_sccs; };
	private:
		std::vector<SCC> m_sccs;
		SCC scc_;                 // SCC atual sendo construído
		GraphNode* prevNode_;     // Último nó visitado
	};

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

	/**
	 * \brief Metodo auxiliar
	 *
	 * \see Algorithms::dfs()
	 */
	static void dfs_visit(GraphNode* node, std::size_t* time,
		std::unordered_map<GraphNode*, GraphNodeColor, GraphNodeHash, GraphNodeEqual>* coloring,
		std::unordered_map<GraphNode*, DiscoveryTime, GraphNodeHash, GraphNodeEqual>* start,
		std::unordered_map<GraphNode*, FinishingTime, GraphNodeHash, GraphNodeEqual>* finish,
		NodeVisitor* nodeVisitor) {
		(*time)++;
		(*start)[node] = *time;
		(*coloring)[node] = GraphNodeColor::DISCOVERED;

		nodeVisitor->visit(node);

		for (GraphEdge& edge : node->getEdges())
			if (GraphNode* target = edge.getTarget(); (*coloring)[target] == GraphNodeColor::UNDISCOVERED)
				dfs_visit(target, time, coloring, start, finish, nodeVisitor);

		(*coloring)[node] = GraphNodeColor::FINISHED;
		(*time)++;
		(*finish)[node] = *time;
	}

	/**
	 * \brief Metodo auxiliar
	 *
	 * \see Algorithms::dfs()
	 */
	static void bfs_visit(GraphNode* node, std::size_t* time,
		std::unordered_map<GraphNode*, GraphNodeColor, GraphNodeHash, GraphNodeEqual>* coloring,
		std::unordered_map<GraphNode*, DiscoveryTime, GraphNodeHash, GraphNodeEqual>* start,
		std::unordered_map<GraphNode*, FinishingTime, GraphNodeHash, GraphNodeEqual>* finish,
		NodeVisitor* nodeVisitor) {
		(*time)++;
		(*start)[node] = *time;
		(*coloring)[node] = GraphNodeColor::DISCOVERED;

		nodeVisitor->visit(node);

		for (GraphEdge& edge : node->getEdges())
			if (GraphNode* target = edge.getTarget(); (*coloring)[target] == GraphNodeColor::UNDISCOVERED)
				bfs_visit(target, time, coloring, start, finish, nodeVisitor);

		(*coloring)[node] = GraphNodeColor::FINISHED;
		(*time)++;
		(*finish)[node] = *time;
	}

	/**
	* \brief
	*/
	std::vector<GraphNode> sortNodesByFinishingTime(
		std::vector<GraphNode>& nodes,
		std::unordered_map<GraphNode*, FinishingTime, GraphNodeHash, GraphNodeEqual>& finishingTime) {
		std::vector<GraphNode*> nodePointers;
		for (auto& node : nodes) {
			nodePointers.push_back(&node);
		}

		std::size_t n = nodePointers.size();
		for (std::size_t i = 0; i < n - 1; ++i) {
			for (std::size_t j = 0; j < n - i - 1; ++j) {
				if (finishingTime[nodePointers[j]] < finishingTime[nodePointers[j + 1]]) {
					std::swap(nodePointers[j], nodePointers[j + 1]);
				}
			}
		}

		std::vector<GraphNode> nodes2;
		for (auto node : nodePointers) {
			nodes2.push_back(*node);
		}

		return nodes2;
	}
}

DFS_DATA Algorithms::DFS(Graph* graph, NodeVisitor* nodeVisitor) {
	return Algorithms::DFS(graph->getNodes(), nodeVisitor);
}

DFS_DATA Algorithms::DFS(std::vector<GraphNode>& visitingNodes, NodeVisitor* nodeVisitor) {
	std::unordered_map<GraphNode*, GraphNodeColor, GraphNodeHash, GraphNodeEqual> coloring;
	std::unordered_map<GraphNode*, DiscoveryTime, GraphNodeHash, GraphNodeEqual> start;
	std::unordered_map<GraphNode*, FinishingTime, GraphNodeHash, GraphNodeEqual> finish;

	for (GraphNode& node : visitingNodes) {
		coloring[&node] = GraphNodeColor::UNDISCOVERED;
		start[&node] = 0;
		finish[&node] = 0;
	}

	std::size_t time = 0;

	for (GraphNode& node : visitingNodes)
		if (coloring[&node] == GraphNodeColor::UNDISCOVERED)
			dfs_visit(&node, &time, &coloring, &start, &finish, nodeVisitor);

	return std::make_tuple(coloring, start, finish);;
}

void Algorithms::BFS(Graph* graph, NodeVisitor* nodeVisitor) {
	Algorithms::BFS(graph->getNodes(), nodeVisitor);
}

void Algorithms::BFS(std::vector<GraphNode>& visitingNodes, NodeVisitor* nodeVisitor) {
	std::unordered_map<GraphNode*, bool, GraphNodeHash, GraphNodeEqual> visited;
	std::queue<GraphNode*> queue;

	queue.push(&visitingNodes[0]);
	visited[&visitingNodes[0]] = true;

	while (!queue.empty()) {
		GraphNode* current = queue.front();
		queue.pop();

		nodeVisitor->visit(current);

		for (GraphEdge& edge : current->getEdges()) {
			GraphNode* neighbor = edge.getTarget();
			if (!visited[neighbor]) {
				queue.push(neighbor);
				visited[neighbor] = true;
			}
		}
	}
}

void Algorithms::transposeGraph(Graph& graph) {
	std::unordered_map<std::size_t, std::vector<GraphNode*>> invertedEdges;

	for (auto& node : graph.getNodes()) {
		for (const auto& edge : node.getEdges()) {
			invertedEdges[edge.getTarget()->getIndex()].push_back(&node);
		}
	}

	for (auto& node : graph.getNodes()) {
		node.setEdges({});
	}

	for (auto& node : graph.getNodes()) {
		for (GraphNode* sourceNode : invertedEdges[node.getIndex()]) {
			node.connect(sourceNode);
		}
	}
}


std::vector<SCC> Algorithms::Kosaraju(Graph* graph) {
	NullNodeVisitor nullVisitor = NullNodeVisitor();
	DFS_DATA data = Algorithms::DFS(graph, &nullVisitor);
	auto& finishingTime = std::get<2>(data);

	Algorithms::transposeGraph(*graph);

	std::vector<GraphNode> nodes2 = sortNodesByFinishingTime(graph->getNodes(), finishingTime);

	SCCNodeVisitor visitor = SCCNodeVisitor();
	Algorithms::DFS(nodes2, &visitor);
	visitor.finalize();

	Algorithms::transposeGraph(*graph);

	return visitor.getSCCS();
}

std::unordered_map<GraphNode*, int, GraphNodeHash, GraphNodeEqual> Algorithms::Dijkstra(Graph* graph, GraphNode& source) {
	// Define a distância inicial como infinito
	std::unordered_map<GraphNode*, int, GraphNodeHash, GraphNodeEqual> distances;
	for (GraphNode& node : graph->getNodes()) {
		distances[&node] = std::numeric_limits<int>::max();
	}
	distances[&source] = 0;

	// Fila de prioridade para selecionar o nodo com a menor distância
	using NodeDistPair = std::pair<int, GraphNode*>;
	std::priority_queue<NodeDistPair, std::vector<NodeDistPair>, std::greater<NodeDistPair>> queue;
	queue.push({ 0, &source });

	while (!queue.empty()) {
		int distance = queue.top().first;
		GraphNode* current = queue.top().second;
		queue.pop();

		// Ignorar se a distância é maior do que a registrada
		int curretDistance = distances[current];
		if (distance > curretDistance) continue;

		// Verificar vizinhos
		for (const GraphEdge& edge : current->getEdges()) {
			GraphNode* neighbor = edge.getTarget();
			int newDist = distances[current] + edge.getFlow();

			// Atualizar a distância se o caminho atual é mais curto
			if (newDist < distances[neighbor]) {
				distances[neighbor] = newDist;
				queue.push({ newDist, neighbor });
			}
		}
	}

	return distances;
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
				std::pair<int,int> key = std::make_pair(edge->getSource()->getIndex(), edge->getTarget()->getIndex());
				edgeFlow[key] = edge->getFlow();
			}
		}
	}

	return std::make_pair<>(maxFlow, edgeFlow);
}