#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <vector>
#include <unordered_map>
#include "GraphEdge.h"

class GraphEdge;
class GraphNode;

/**
 * \class NodeVisitor
 * \brief
 */
class NodeVisitor {
public:
	/**
	 * \brief
	 */
	virtual ~NodeVisitor() = default;

	/**
	 * \brief
	 */
	virtual void visit(GraphNode* node) = 0;
};

/**
 * \class GraphNode
 * \brief Representa um n� (v�rtice) em um grafo.
 *
 * Um n� em um grafo pode estar conectado a outros n�s atrav�s de arestas
 * (GraphEdges). Esta classe fornece funcionalidades para acessar as arestas
 * conectadas ao n�.
 */
class GraphNode {
public:
	/**
	 * \brief Construtor padr�o de GraphNode.
	 *
	 * Cria uma inst�ncia de GraphNode sem arestas conectadas inicialmente.
	 */
	GraphNode();

	/**
	 *
	 */
	GraphNode(std::size_t index);

	/**
	 *
	 */
	GraphNode(std::size_t index, int demand);

	/**
	 *
	 */
	std::size_t getIndex() const;

	/**
	 * \brief Conecta dois GraphNodes.
	 */
	void connect(GraphNode* node);

	/**
	 *
	 */
	void connect(GraphNode* node, int weight);

	/**
	 *
	 */
	void disconnect(GraphNode* node);

	/**
	 *
	 */
	bool isConnected(GraphNode* node);

	/**
	 *
	 */
	int getDemand() const;

	/**
	 * \brief Obt�m as arestas conectadas ao n�.
	 * \return Um vetor de ponteiros para GraphEdges conectadas a este n�.
	 *
	 * Retorna todas as arestas que est�o conectadas ao n� atual, permitindo que
	 * o chamador interaja com as conex�es do n�.
	 */
	std::vector<GraphEdge>& getEdges();

	/**
	 *
	 */
	void setEdges(std::vector<GraphEdge> edges);

	/**
	 *
	 */
	bool operator==(const GraphNode& other) const;

	/**
	 *
	 */
	bool operator!=(const GraphNode& other) const;

	/**
	 *
	 */
	bool operator<(const GraphNode& other) const;

	/**
	 *
	 */
	struct GraphNodeHash {
		std::size_t operator()(const GraphNode* k) const {
			return std::hash<std::size_t>()(k->getIndex());
		}
	};

	/**
	 *
	 */
	struct GraphNodeEqual {
		bool operator()(const GraphNode* lhs, const GraphNode* rhs) const {
			return *lhs == *rhs;
		}
	};

	/**
	 *
	 */
	template<typename T>
	static std::unordered_map<GraphNode*, T, GraphNodeHash, GraphNodeEqual> map() {
		return std::unordered_map<GraphNode*, T, GraphNodeHash, GraphNodeEqual>();
	}
private:
	/**
	 * \brief Armazena as arestas conectadas ao n�.
	 *
	 * Um vetor que cont�m ponteiros para as arestas (GraphEdges) que conectam este n�
	 * a outros n�s. Cada aresta aponta para outro n� no grafo.
	 */
	std::vector<GraphEdge> m_edges;

	/**
	 *
	 */
	std::size_t m_index;

	/**
	 *
	 */
	int m_demand;
};


namespace std {
	template <>

	/**
	 *
	 */
	struct hash<GraphNode> {
		std::size_t operator()(const GraphNode node) const {
			return std::hash<std::size_t>()(node.getIndex());
		}
	};
}
#endif // GRAPHNODE_H
