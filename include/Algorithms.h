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
	 * \brief Implementa��o do algoritmo de Edmonds-Karp.
	 *
	 * \details O algoritmo Edmonds-Karp � uma implementa��o espec�fica do m�todo de fluxo m�ximo de Ford-Fulkerson,
	 *          utilizando busca em largura (BFS) para encontrar caminhos aumentantes.
	 *          � garantido que termina em um n�mero finito de itera��es, pois o aumento no fluxo � limitado pelo
	 *          n�mero de arestas e capacidades.
	 *
	 * \param graph Ponteiro para o grafo onde o fluxo ser� calculado.
	 * \param source Ponteiro para o n� de origem no grafo.
	 * \param sink Ponteiro para o n� de destino no grafo.
	 *
	 * \return O valor do fluxo m�ximo encontrado.
	 *
	 * \complexidade O(VE^2), onde V � o n�mero de n�s e E � o n�mero de arestas no grafo.
	 *               Isso ocorre porque cada aresta � saturada no m�ximo O(V) vezes, e cada execu��o de BFS
	 *               leva tempo O(V + E).
	 */
	static int EdmondKarp(Graph* graph, GraphNode* source, GraphNode* sink);
};

#endif // ALGORITHMS_H
