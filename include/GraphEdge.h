#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include "GraphNode.h"

class GraphNode;

/**
 * \class GraphEdge
 * \brief Representa uma aresta (conex�o) entre dois n�s em um grafo.
 *
 * Uma GraphEdge conecta dois n�s (GraphNodes) em um grafo, criando uma rela��o
 * de vizinhan�a entre os n�s.
 */
class GraphEdge {
public:
	/**
	 * \brief Construtor de GraphEdge.
	 * \param source N� de origem da aresta.
	 * \param target N� de destino da aresta.
	 *
	 * Cria uma aresta que conecta o n� de origem ao n� de destino.
	 */
	GraphEdge(GraphNode* source, GraphNode* target);

	/**
	 * \brief Construtor de GraphEdge.
	 * \param source N� de origem da aresta.
	 * \param target N� de destino da aresta.
	 * \param weight Peso.
	 *
	 * Cria uma aresta que conecta o n� de origem ao n� de destino.
	 */
	GraphEdge(GraphNode* source, GraphNode* target, int weight);

	/**
	 * \brief Obt�m o n� de origem da aresta.
	 * \return Ponteiro para o n� de origem.
	 *
	 * Retorna o n� de onde a aresta se origina.
	 */
	GraphNode* getSource() const;

	/**
	 * \brief Obt�m o n� de destino da aresta.
	 * \return Ponteiro para o n� de destino.
	 *
	 * Retorna o n� para onde a aresta aponta.
	 */
	GraphNode* getTarget() const;

	/**
	 *
	 */
	GraphEdge* getReverse();

	/**
	 *
	 */
	void setFlow(int flow) { m_flow = flow; };

	/**
	 *
	 */
	int getFlow() const { return m_flow; };

	/**
	 *
	 */
	int getCapacity() const { return m_capacity; };

	/**
	 *
	 */
	bool operator==(const GraphEdge& other) const;
private:
	/**
	 * \brief O n� de origem da aresta.
	 *
	 * Armazena o n� de onde a aresta se origina.
	 */
	GraphNode* m_source;

	/**
	 * \brief O n� de destino da aresta.
	 *
	 * Armazena o n� para onde a aresta aponta.
	 */
	GraphNode* m_target;

	/**
	 *
	 */
	int m_capacity;

	/**
	 *
	 */
	int m_flow;

	/**
	 *
	 */
	GraphEdge* m_reverse;
};
#endif // GRAPHEDGE_H
