#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <vector>
#include <unordered_map>
#include "GraphEdge.h"

class GraphEdge;
class GraphNode;

/**
 * \class NodeVisitor
 * \brief Representa uma interface para visitar n�s em um grafo.
 *
 * Esta classe � usada para definir comportamentos personalizados ao visitar n�s
 * (GraphNode) em um grafo.
 */
class NodeVisitor {
public:
	/**
	 * \brief Destrutor virtual padr�o.
	 */
	virtual ~NodeVisitor() = default;

	/**
	 * \brief M�todo virtual para visitar um n� do grafo.
	 *
	 * Deve ser implementado por classes derivadas para definir a��es
	 * personalizadas ao visitar um n�.
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
	 * \brief Construtor que inicializa um GraphNode com um �ndice.
	 * \param index O �ndice associado ao n�.
	 */
	GraphNode(std::size_t index);

	/**
	 * \brief Construtor que inicializa um GraphNode com um �ndice e demanda.
	 * \param index O �ndice associado ao n�.
	 * \param demand A demanda associada ao n�.
	 */
	GraphNode(std::size_t index, int demand);

	/**
	 * \brief Obt�m o �ndice do n�.
	 * \return O �ndice do n� como um tamanho (std::size_t).
	 */
	std::size_t getIndex() const;

	/**
	 * \brief Conecta este n� a outro n�.
	 * \param node Ponteiro para o n� a ser conectado.
	 */
	void connect(GraphNode* node);

	/**
	 * \brief Conecta este n� a outro n� com um peso associado.
	 * \param node Ponteiro para o n� a ser conectado.
	 * \param weight O peso da aresta que conecta os n�s.
	 */
	void connect(GraphNode* node, int weight);

	/**
	 * \brief Desconecta este n� de outro n�.
	 * \param node Ponteiro para o n� a ser desconectado.
	 */
	void disconnect(GraphNode* node);

	/**
	 * \brief Verifica se este n� est� conectado a outro n�.
	 * \param node Ponteiro para o n� a ser verificado.
	 * \return Verdadeiro se os n�s est�o conectados, falso caso contr�rio.
	 */
	bool isConnected(GraphNode* node);

	/**
	 * \brief Obt�m a demanda associada ao n�.
	 * \return A demanda como um inteiro.
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
	 * \brief Define as arestas conectadas ao n�.
	 * \param edges Um vetor de arestas para substituir as conex�es atuais.
	 */
	void setEdges(std::vector<GraphEdge> edges);

	/**
	 * \brief Operador de igualdade para comparar dois n�s.
	 * \param other O n� a ser comparado.
	 * \return Verdadeiro se os n�s s�o iguais, falso caso contr�rio.
	 */
	bool operator==(const GraphNode& other) const;

	/**
	 * \brief Operador de desigualdade para comparar dois n�s.
	 * \param other O n� a ser comparado.
	 * \return Verdadeiro se os n�s s�o diferentes, falso caso contr�rio.
	 */
	bool operator!=(const GraphNode& other) const;

	/**
	 * \brief Operador de ordena��o para comparar dois n�s.
	 * \param other O n� a ser comparado.
	 * \return Verdadeiro se este n� � menor que o outro n�.
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
	 * \brief Armazena as arestas conectadas ao n�.
	 *
	 * Um vetor que cont�m ponteiros para as arestas (GraphEdges) que conectam este n�
	 * a outros n�s. Cada aresta aponta para outro n� no grafo.
	 */
	std::vector<GraphEdge> m_edges;

	/**
	 * \brief �ndice �nico associado ao n�.
	 */
	std::size_t m_index;

	/**
	 * \brief Demanda associada ao n�.
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
