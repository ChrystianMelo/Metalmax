#include <boost/test/unit_test.hpp>

#include "Graph.h"
#include "GraphNode.h"
#include "Algorithms.h"

/**
 * \brief Teste 1: Grafo extremamente simples
 *
 * Grafo com 2 nós (source e sink) e uma única aresta S->T
 * Capacidade = 10
 * Esperado: Fluxo máximo = 10
 */
BOOST_AUTO_TEST_CASE(TestSingleEdge)
{
	// Cria nós
	GraphNode nodeS(0);  // Source
	GraphNode nodeT(1);  // Sink

	// Cria as arestas (S->T e T->S reversa)
	nodeS.connect(&nodeT, 10);

	// Monta o grafo
	Graph graph({ &nodeS, &nodeT });

	// Executa Edmond-Karp
	int maxFlow = Algorithms::EdmondKarp(&graph, &graph.getNodes()[0], &graph.getNodes()[1]
		BOOST_CHECK(maxFlow == 10); // Deve ser 10
}

/**
 * \brief Teste 2: Grafo com múltiplos caminhos
 *
 * Estrutura:
 *   (S) --10--> (1) --5--> (3) --10--> (T)
 *    \                       ^
 *     \--10--> (2) --5------/
 *
 * Esperado:
 *   - caminho S->1->3->T pode levar até 5
 *   - caminho S->2->3->T pode levar até 5
 *   - total = 10
 */
BOOST_AUTO_TEST_CASE(TestMultiplePaths)
{
	// Cria nós
	GraphNode nodeS(0);   // Source
	GraphNode node1(1);
	GraphNode node2(2);
	GraphNode node3(3);
	GraphNode nodeT(4);   // Sink

	// Conexões a partir de S
	nodeS.connect(&node1, 10);  // S->1
	nodeS.connect(&node2, 10);  // S->2

	// Conexões intermediárias
	node1.connect(&node3, 5);   // 1->3
	node2.connect(&node3, 5);   // 2->3

	// Conexão para T
	node3.connect(&nodeT, 10);  // 3->T

	// Monta o grafo
	Graph graph({ &nodeS, &node1, &node2, &node3, &nodeT });

	// Executa Edmond-Karp
	int maxFlow = Algorithms::EdmondKarp(&graph, &graph.getNodes()[0], &graph.getNodes()[4]);

	// Fluxo deve ser 10 (5 passando por S->1->3->T e 5 passando por S->2->3->T)
	BOOST_CHECK(maxFlow == 10);
}

/**
 * \brief Teste 3: Grafo sem caminho (S e T desconexos)
 *
 *   (S) --10--> (1)   e   (T) --10--> (2)
 *
 * Não há aresta ligando (1) a (T) ou (S) a (2).
 * Logo, fluxo máximo = 0.
 */
BOOST_AUTO_TEST_CASE(TestNoPath)
{
	// Cria nós
	GraphNode nodeS(0);  // Source
	GraphNode node1(1);
	GraphNode nodeT(2);  // Sink
	GraphNode node2(3);  // Nó isolado para T

	// S->1
	nodeS.connect(&node1, 10);

	// T->2
	// Este "connect" não ajuda, pois não conecta no 'source' ou nós intermediários.
	nodeT.connect(&node2, 10);

	// Monta o grafo
	Graph graph({ &nodeS, &node1, &nodeT, &node2 });

	// Executa Edmond-Karp
	int maxFlow = Algorithms::EdmondKarp(&graph, &graph.getNodes()[0], &graph.getNodes()[2]);

	// Valida
	BOOST_CHECK(maxFlow == 0); // sem caminho, fluxo = 0
}