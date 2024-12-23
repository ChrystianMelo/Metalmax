#include <boost/test/unit_test.hpp>

#include "Graph.h"
#include "GraphNode.h"
#include "Algorithms.h"

/**
 * \brief Teste 1: Grafo extremamente simples
 *
 * Grafo com 2 n�s (source e sink) e uma �nica aresta S->T
 * Capacidade = 10
 * Esperado: Fluxo m�ximo = 10
 */
BOOST_AUTO_TEST_CASE(TestSingleEdge)
{
	// Cria n�s
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
 * \brief Teste 2: Grafo com m�ltiplos caminhos
 *
 * Estrutura:
 *   (S) --10--> (1) --5--> (3) --10--> (T)
 *    \                       ^
 *     \--10--> (2) --5------/
 *
 * Esperado:
 *   - caminho S->1->3->T pode levar at� 5
 *   - caminho S->2->3->T pode levar at� 5
 *   - total = 10
 */
BOOST_AUTO_TEST_CASE(TestMultiplePaths)
{
	// Cria n�s
	GraphNode nodeS(0);   // Source
	GraphNode node1(1);
	GraphNode node2(2);
	GraphNode node3(3);
	GraphNode nodeT(4);   // Sink

	// Conex�es a partir de S
	nodeS.connect(&node1, 10);  // S->1
	nodeS.connect(&node2, 10);  // S->2

	// Conex�es intermedi�rias
	node1.connect(&node3, 5);   // 1->3
	node2.connect(&node3, 5);   // 2->3

	// Conex�o para T
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
 * N�o h� aresta ligando (1) a (T) ou (S) a (2).
 * Logo, fluxo m�ximo = 0.
 */
BOOST_AUTO_TEST_CASE(TestNoPath)
{
	// Cria n�s
	GraphNode nodeS(0);  // Source
	GraphNode node1(1);
	GraphNode nodeT(2);  // Sink
	GraphNode node2(3);  // N� isolado para T

	// S->1
	nodeS.connect(&node1, 10);

	// T->2
	// Este "connect" n�o ajuda, pois n�o conecta no 'source' ou n�s intermedi�rios.
	nodeT.connect(&node2, 10);

	// Monta o grafo
	Graph graph({ &nodeS, &node1, &nodeT, &node2 });

	// Executa Edmond-Karp
	int maxFlow = Algorithms::EdmondKarp(&graph, &graph.getNodes()[0], &graph.getNodes()[2]);

	// Valida
	BOOST_CHECK(maxFlow == 0); // sem caminho, fluxo = 0
}