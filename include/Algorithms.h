#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>


#include "Graph.h"
#include "Requester.h"
#include "Receiver.h"

enum GraphNodeColor {
	// Não foi descobreto.
	UNDISCOVERED,
	// Descoberto mas não finalizado.
	DISCOVERED,
	// Finalizado.
	FINISHED
};


using GraphNodeHash = GraphNode::GraphNodeHash;
using GraphNodeEqual = GraphNode::GraphNodeEqual;
using DiscoveryTime = std::size_t;
using FinishingTime = std::size_t;
using DFS_DATA = std::tuple<
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
	 * \brief Executa o algoritmo de casamento estável de Gale-Shapley.
	 *
	 * \details O algoritmo tenta encontrar um casamento estável entre Requesters (solicitantes) e Receivers (receptores)
	 * baseando-se em listas de prioridade. Requesters fazem propostas para Receivers e os Receivers
	 * aceitam ou rejeitam as propostas de acordo com suas preferências. O objetivo é garantir um casamento
	 * estável, onde não existam dois elementos que prefiram um ao outro em detrimento de seus parceiros atuais.
	 *
	 * \note Complexidade O(n^2), onde n é o número de Requesters (e o mesmo para os Receivers).
	 *
	 * \param men Vetor de Requesters (solicitantes) participantes no algoritmo.
	 */
	static void GaleShapley(const std::vector<Requester*>& men);

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
};

#endif // ALGORITHMS_H
