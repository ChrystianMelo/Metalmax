#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include "GraphNode.h"

class GraphNode;

/**
 * \class GraphEdge
 * \brief Representa uma aresta (conexão) entre dois nós em um grafo.
 *
 * Uma GraphEdge conecta dois nós (GraphNodes) em um grafo, criando uma relação
 * de vizinhança entre os nós.
 */
class GraphEdge {
public:
	/**
	 * \brief Construtor de GraphEdge.
	 * \param source Nó de origem da aresta.
	 * \param target Nó de destino da aresta.
	 *
	 * Cria uma aresta que conecta o nó de origem ao nó de destino.
	 */
	GraphEdge(GraphNode* source, GraphNode* target);

	/**
	 * \brief Construtor de GraphEdge com peso.
	 * \param source Nó de origem da aresta.
	 * \param target Nó de destino da aresta.
	 * \param weight Peso da aresta.
	 *
	 * Cria uma aresta que conecta o nó de origem ao nó de destino com um peso associado.
	 */
	GraphEdge(GraphNode* source, GraphNode* target, int weight);

	/**
	 * \brief Obtém o nó de origem da aresta.
	 * \return Ponteiro para o nó de origem.
	 *
	 * Retorna o nó de onde a aresta se origina.
	 */
	GraphNode* getSource() const;

	/**
	 * \brief Obtém o nó de destino da aresta.
	 * \return Ponteiro para o nó de destino.
	 *
	 * Retorna o nó para onde a aresta aponta.
	 */
	GraphNode* getTarget() const;

	/**
	 * \brief Obtém a aresta reversa correspondente no grafo residual.
	 * \return Ponteiro para a aresta reversa.
	 *
	 * Retorna a aresta reversa associada no grafo residual, permitindo
	 * manipulação do fluxo em algoritmos de fluxo máximo.
	 */
	GraphEdge* getReverse();

	/**
	 * \brief Define o fluxo da aresta.
	 * \param flow Valor do fluxo a ser definido.
	 *
	 * Atualiza o fluxo associado à aresta.
	 */
	void setFlow(int flow) { m_flow = flow; };

	/**
	 * \brief Obtém o fluxo da aresta.
	 * \return O valor do fluxo da aresta.
	 *
	 * Retorna o fluxo atual que passa por esta aresta.
	 */
	int getFlow() const { return m_flow; };

	/**
	 * \brief Obtém a capacidade da aresta.
	 * \return A capacidade da aresta.
	 *
	 * Retorna a capacidade máxima de fluxo que a aresta pode suportar.
	 */
	int getCapacity() const { return m_capacity; };

	/**
	 * \brief Operador de igualdade para comparar duas arestas.
	 * \param other A outra aresta a ser comparada.
	 * \return Verdadeiro se as arestas são iguais, falso caso contrário.
	 */
	bool operator==(const GraphEdge& other) const;

private:
	/**
	 * \brief O nó de origem da aresta.
	 *
	 * Armazena o nó de onde a aresta se origina.
	 */
	GraphNode* m_source;

	/**
	 * \brief O nó de destino da aresta.
	 *
	 * Armazena o nó para onde a aresta aponta.
	 */
	GraphNode* m_target;

	/**
	 * \brief O fluxo atual na aresta.
	 *
	 * Representa a quantidade de fluxo que atualmente passa por esta aresta.
	 */
	int m_flow;

	/**
	 * \brief A capacidade máxima da aresta.
	 *
	 * Indica o fluxo máximo que a aresta pode suportar.
	 */
	int m_capacity;

	/**
	 * \brief A aresta reversa no grafo residual.
	 *
	 * Aponta para a aresta reversa correspondente no grafo residual.
	 */
	GraphEdge* m_reverse;
};

#endif // GRAPHEDGE_H
