#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <vector>
#include <unordered_map>
#include "GraphEdge.h"

class GraphEdge;
class GraphNode;

/**
 * \class NodeVisitor
 * \brief Representa uma interface para visitar nós em um grafo.
 *
 * Esta classe é usada para definir comportamentos personalizados ao visitar nós
 * (GraphNode) em um grafo.
 */
class NodeVisitor {
public:
	/**
	 * \brief Destrutor virtual padrão.
	 */
	virtual ~NodeVisitor() = default;

	/**
	 * \brief Método virtual para visitar um nó do grafo.
	 *
	 * Deve ser implementado por classes derivadas para definir ações
	 * personalizadas ao visitar um nó.
	 */
	virtual void visit(GraphNode* node) = 0;
};

/**
 * \class GraphNode
 * \brief Representa um nó (vértice) em um grafo.
 *
 * Um nó em um grafo pode estar conectado a outros nós através de arestas
 * (GraphEdges). Esta classe fornece funcionalidades para acessar as arestas
 * conectadas ao nó.
 */
class GraphNode {
public:
	/**
	 * \brief Construtor padrão de GraphNode.
	 *
	 * Cria uma instância de GraphNode sem arestas conectadas inicialmente.
	 */
	GraphNode();

	/**
	 * \brief Construtor que inicializa um GraphNode com um índice.
	 * \param index O índice associado ao nó.
	 */
	GraphNode(std::size_t index);

	/**
	 * \brief Construtor que inicializa um GraphNode com um índice e demanda.
	 * \param index O índice associado ao nó.
	 * \param demand A demanda associada ao nó.
	 */
	GraphNode(std::size_t index, int demand);

	/**
	 * \brief Obtém o índice do nó.
	 * \return O índice do nó como um tamanho (std::size_t).
	 */
	std::size_t getIndex() const;

	/**
	 * \brief Conecta este nó a outro nó.
	 * \param node Ponteiro para o nó a ser conectado.
	 */
	void connect(GraphNode* node);

	/**
	 * \brief Conecta este nó a outro nó com um peso associado.
	 * \param node Ponteiro para o nó a ser conectado.
	 * \param weight O peso da aresta que conecta os nós.
	 */
	void connect(GraphNode* node, int weight);

	/**
	 * \brief Desconecta este nó de outro nó.
	 * \param node Ponteiro para o nó a ser desconectado.
	 */
	void disconnect(GraphNode* node);

	/**
	 * \brief Verifica se este nó está conectado a outro nó.
	 * \param node Ponteiro para o nó a ser verificado.
	 * \return Verdadeiro se os nós estão conectados, falso caso contrário.
	 */
	bool isConnected(GraphNode* node);

	/**
	 * \brief Obtém a demanda associada ao nó.
	 * \return A demanda como um inteiro.
	 */
	int getDemand() const;

	/**
	 * \brief Obtém as arestas conectadas ao nó.
	 * \return Um vetor de ponteiros para GraphEdges conectadas a este nó.
	 *
	 * Retorna todas as arestas que estão conectadas ao nó atual, permitindo que
	 * o chamador interaja com as conexões do nó.
	 */
	std::vector<GraphEdge>& getEdges();

	/**
	 * \brief Define as arestas conectadas ao nó.
	 * \param edges Um vetor de arestas para substituir as conexões atuais.
	 */
	void setEdges(std::vector<GraphEdge> edges);

	/**
	 * \brief Operador de igualdade para comparar dois nós.
	 * \param other O nó a ser comparado.
	 * \return Verdadeiro se os nós são iguais, falso caso contrário.
	 */
	bool operator==(const GraphNode& other) const;

	/**
	 * \brief Operador de desigualdade para comparar dois nós.
	 * \param other O nó a ser comparado.
	 * \return Verdadeiro se os nós são diferentes, falso caso contrário.
	 */
	bool operator!=(const GraphNode& other) const;

	/**
	 * \brief Operador de ordenação para comparar dois nós.
	 * \param other O nó a ser comparado.
	 * \return Verdadeiro se este nó é menor que o outro nó.
	 */
	bool operator<(const GraphNode& other) const;

	/**
	 * \struct GraphNodeHash
	 * \brief Functor para calcular o hash de um ponteiro para GraphNode.
	 */
	struct GraphNodeHash {
		std::size_t operator()(const GraphNode* k) const {
			return std::hash<std::size_t>()(k->getIndex());
		}
	};

	/**
	 * \struct GraphNodeEqual
	 * \brief Functor para comparar dois ponteiros para GraphNode.
	 */
	struct GraphNodeEqual {
		bool operator()(const GraphNode* lhs, const GraphNode* rhs) const {
			return *lhs == *rhs;
		}
	};

	/**
	 * \brief Cria um mapa hash baseado em GraphNode como chave.
	 * \tparam T O tipo de valor armazenado no mapa.
	 * \return Um mapa hash com GraphNode como chave.
	 */
	template<typename T>
	static std::unordered_map<GraphNode*, T, GraphNodeHash, GraphNodeEqual> map() {
		return std::unordered_map<GraphNode*, T, GraphNodeHash, GraphNodeEqual>();
	}
private:
	/**
	 * \brief Armazena as arestas conectadas ao nó.
	 *
	 * Um vetor que contém ponteiros para as arestas (GraphEdges) que conectam este nó
	 * a outros nós. Cada aresta aponta para outro nó no grafo.
	 */
	std::vector<GraphEdge> m_edges;

	/**
	 * \brief Índice único associado ao nó.
	 */
	std::size_t m_index;

	/**
	 * \brief Demanda associada ao nó.
	 */
	int m_demand;
};

namespace std {
	template <>
	/**
	 * \brief Functor para calcular o hash de GraphNode.
	 */
	struct hash<GraphNode> {
		std::size_t operator()(const GraphNode node) const {
			return std::hash<std::size_t>()(node.getIndex());
		}
	};
}
#endif // GRAPHNODE_H
