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
	 * \brief Construtor de GraphEdge com peso.
	 * \param source N� de origem da aresta.
	 * \param target N� de destino da aresta.
	 * \param weight Peso da aresta.
	 *
	 * Cria uma aresta que conecta o n� de origem ao n� de destino com um peso associado.
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
	 * \brief Obt�m a aresta reversa correspondente no grafo residual.
	 * \return Ponteiro para a aresta reversa.
	 *
	 * Retorna a aresta reversa associada no grafo residual, permitindo
	 * manipula��o do fluxo em algoritmos de fluxo m�ximo.
	 */
	GraphEdge* getReverse();

	/**
	 * \brief Define o fluxo da aresta.
	 * \param flow Valor do fluxo a ser definido.
	 *
	 * Atualiza o fluxo associado � aresta.
	 */
	void setFlow(int flow) { m_flow = flow; };

	/**
	 * \brief Obt�m o fluxo da aresta.
	 * \return O valor do fluxo da aresta.
	 *
	 * Retorna o fluxo atual que passa por esta aresta.
	 */
	int getFlow() const { return m_flow; };

	/**
	 * \brief Obt�m a capacidade da aresta.
	 * \return A capacidade da aresta.
	 *
	 * Retorna a capacidade m�xima de fluxo que a aresta pode suportar.
	 */
	int getCapacity() const { return m_capacity; };

	/**
	 * \brief Operador de igualdade para comparar duas arestas.
	 * \param other A outra aresta a ser comparada.
	 * \return Verdadeiro se as arestas s�o iguais, falso caso contr�rio.
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
	 * \brief O fluxo atual na aresta.
	 *
	 * Representa a quantidade de fluxo que atualmente passa por esta aresta.
	 */
	int m_flow;

	/**
	 * \brief A capacidade m�xima da aresta.
	 *
	 * Indica o fluxo m�ximo que a aresta pode suportar.
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
