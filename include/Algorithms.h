#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <unordered_map>

#include "Graph.h"

/**
 * \class Algorithms
 *
 * \brief Algotimos aprendidos a partir do livro Algorithm Design de Jon Kleinberg
 */
class Algorithms {
public:
	/**
	 * \brief Implementação do algoritmo de Edmonds-Karp.
	 *
	 * \details O algoritmo Edmonds-Karp é uma implementação específica do método de fluxo máximo de Ford-Fulkerson,
	 *          utilizando busca em largura (BFS) para encontrar caminhos aumentantes.
	 *          É garantido que termina em um número finito de iterações, pois o aumento no fluxo é limitado pelo
	 *          número de arestas e capacidades.
	 *
	 * \param graph Ponteiro para o grafo onde o fluxo será calculado.
	 * \param source Ponteiro para o nó de origem no grafo.
	 * \param sink Ponteiro para o nó de destino no grafo.
	 *
	 * \return O valor do fluxo máximo encontrado.
	 *
	 * \complexidade O(VE^2), onde V é o número de nós e E é o número de arestas no grafo.
	 *               Isso ocorre porque cada aresta é saturada no máximo O(V) vezes, e cada execução de BFS
	 *               leva tempo O(V + E).
	 */
	static int EdmondKarp(Graph* graph, GraphNode* source, GraphNode* sink);
};

#endif // ALGORITHMS_H
