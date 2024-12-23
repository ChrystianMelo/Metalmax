#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>


#include "Graph.h"
enum GraphNodeColor {
	// Não foi descobreto.
	UNDISCOVERED,
	// Descoberto mas não finalizado.
	DISCOVERED,
	// Finalizado.
	FINISHED
};

struct PairHash {
	std::size_t operator()(const std::pair<int, int>& p) const {
		// Exemplo simples de combinar dois hashes
		// para os ints (p.first e p.second)
		auto h1 = std::hash<int>{}(p.first);
		auto h2 = std::hash<int>{}(p.second);

		// "Combinar" os hashes em um só
		// (Exemplo: técnica proposta por boost::hash_combine)
		// 0x9e3779b97f4a7c15ULL é um "magic number" comum para dispersão
		std::size_t seed = 0;
		// Combina h1:
		seed ^= h1 + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
		// Combina h2:
		seed ^= h2 + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);

		return seed;
	}
};

using GraphNodeHash = GraphNode::GraphNodeHash;
using GraphNodeEqual = GraphNode::GraphNodeEqual;
using DiscoveryTime = std::size_t;
using FinishingTime = std::size_t;
using DFS_DATA = std::tuple<
	std::unordered_map<GraphNode*, GraphNodeColor, GraphNodeHash, GraphNodeEqual>,
	std::unordered_map<GraphNode*, DiscoveryTime, GraphNodeHash, GraphNodeEqual>,
	std::unordered_map<GraphNode*, FinishingTime, GraphNodeHash, GraphNodeEqual>>;
using BFS_DATA = std::tuple<
	std::unordered_map<GraphNode*, GraphNodeColor, GraphNodeHash, GraphNodeEqual>,
	std::unordered_map<GraphNode*, DiscoveryTime, GraphNodeHash, GraphNodeEqual>,
	std::unordered_map<GraphNode*, FinishingTime, GraphNodeHash, GraphNodeEqual>>;
using SCC = std::vector<GraphNode>;

/**
 * \class Algorithms
 *
 * \brief Algotimos aprendidos a partir do livro Algorithm Design de Jon Kleinberg
 */
class Algorithms {
public:
	/**
	 * \brief Realiza uma busca em profundidade (DFS) em um grafo.
	 *
	 * Este método percorre o grafo começando de um nó e visita todos os nós conectados a ele de maneira recursiva,
	 * utilizando o algoritmo de busca em profundidade (Depth-First Search, DFS).
	 *
	 * \param graph Um ponteiro para o objeto 'Graph' que contém os nós e arestas a serem percorridos.
	 * \param visitedNode Um 'std::function' que será executado em cada nó visitado durante a busca.
	 *                    A função aceita um ponteiro para 'GraphNode' como argumento, permitindo que o comportamento
	 *                    durante a visita a cada nó seja personalizado.
	 *
	 * \return *escrever aqui*
	 *
	 * \note Complexidade: O(V + E), onde V é o número de vértices (nós) e E é o número de arestas do grafo.
	 */
	static DFS_DATA DFS(Graph* graph, NodeVisitor* nodeVisitor);

	/**
	 * \brief Realiza uma busca em profundidade (DFS) em um grafo.
	 *
	 * Este método percorre o grafo começando de um nó e visita todos os nós conectados a ele de maneira recursiva,
	 * utilizando o algoritmo de busca em profundidade (Depth-First Search, DFS).
	 *
	 * \param graph Um ponteiro para o objeto 'Graph' que contém os nós e arestas a serem percorridos.
	 * \param visitingNodes
	 * \param nodeVisitor a função aceita um ponteiro para 'GraphNode' como argumento, permitindo que o comportamento
	 *                    durante a visita a cada nó seja personalizado.
	 *
	 * \return *escrever aqui*
	 *
	 * \note Complexidade: O(V + E), onde V é o número de vértices (nós) e E é o número de arestas do grafo.
	 */
	static DFS_DATA DFS(std::vector<GraphNode>& visitingNodes, NodeVisitor* nodeVisitor);

	static void BFS(Graph* graph, NodeVisitor* nodeVisitor);
	static void BFS(std::vector<GraphNode>& visitingNodes, NodeVisitor* nodeVisitor);

	/**
	 *
	 */

	static void transposeGraph(Graph& graph);

	/**
	 *
	 */
	static std::vector<SCC> Kosaraju(Graph* graph);

	/**
	 *
	 */
	static std::unordered_map<GraphNode*, int, GraphNodeHash, GraphNodeEqual> Dijkstra(Graph* graph, GraphNode& source);

	/**
	 *
	 */
	static std::pair<int, std::unordered_map<std::pair<int,int>, int, PairHash>> EdmondKarp(Graph* graph, GraphNode* source, GraphNode* sink);
};

#endif // ALGORITHMS_H
