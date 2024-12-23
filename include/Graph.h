#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "GraphNode.h"

/**
 * \class Graph
 * \brief Representa um grafo contendo m�ltiplos n�s (GraphNodes).
 *
 * Esta classe cont�m uma cole��o de n�s (GraphNodes) que representam os v�rtices
 * do grafo. A classe tamb�m oferece m�todos para acessar e gerenciar esses n�s.
 */
class Graph {
public:
	/**
	 * \brief Construtor padr�o da classe Graph.
	 *
	 * Inicializa um grafo vazio sem nenhum n�. Este construtor cria uma inst�ncia
	 * de 'Graph' sem n�s ou arestas, ideal para ser preenchido posteriormente.
	 */
	Graph() {}

	/**
	 * \brief Construtor da classe Graph com um conjunto de n�s.
	 *
	 * \param nodes Vetor contendo os n�s (GraphNodes) que far�o parte do grafo.
	 *
	 * Este construtor inicializa o grafo com um vetor de n�s fornecido. Ele permite
	 * a cria��o de um grafo j� populado com n�s.
	 */
	Graph(const std::vector<GraphNode*> nodes) : m_nodes(nodes) {}

	/**
	 * \brief Obt�m os n�s do grafo.
	 * \return Refer�ncia ao vetor de GraphNodes presentes no grafo.
	 *
	 * Este m�todo retorna todos os n�s armazenados no grafo. Pode ser usado para
	 * manipular ou acessar os n�s do grafo.
	 */
	std::vector<GraphNode*>& getNodes();

protected:
	/**
	 * \brief Armazena os n�s (GraphNodes) do grafo.
	 *
	 * Um vetor que cont�m todos os n�s (GraphNodes) presentes no grafo. Cada n�
	 * pode estar conectado a outros n�s atrav�s de arestas (GraphEdges).
	 */
	std::vector<GraphNode*> m_nodes;
};

#endif // GRAPH_H
