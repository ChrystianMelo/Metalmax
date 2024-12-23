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
	Graph graph({ nodeS, nodeT });

	// Executa Edmond-Karp
	auto pair = Algorithms::EdmondKarp(&graph, &graph.getNodes()[0], &graph.getNodes()[1]);
	int maxFlow = pair.first;
	// Valida
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
	Graph graph({ nodeS, node1, node2, node3, nodeT });

	// Executa Edmond-Karp
	auto pair = Algorithms::EdmondKarp(&graph, &graph.getNodes()[0], &graph.getNodes()[4]);
	int maxFlow = pair.first;

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
BOOST_AUTO_TEST_CASE( TestNoPath)
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
	Graph graph({ nodeS, node1, nodeT, node2 });

	// Executa Edmond-Karp
	auto pair = Algorithms::EdmondKarp(&graph, &graph.getNodes()[0], &graph.getNodes()[2]);
	int maxFlow = pair.first;

	// Valida
	BOOST_CHECK(maxFlow == 0); // sem caminho, fluxo = 0
}

BOOST_AUTO_TEST_CASE(TestProfessoraExemplo)
{
	GraphNode node1(1, 0); // gerador
	GraphNode node2(2, 20); // demanda=30
	GraphNode node3(3, 30); // demanda=20
	GraphNode node4(4, 40); // demanda=40
	GraphNode node5(5, 50); // demanda=50
	GraphNode node6(6, 50); // demanda=50

	node1.connect(&node2, 50); // 1->2
	node1.connect(&node3, 60); // 1->3
	node1.connect(&node4, 70); // 1->4
	node1.connect(&node5, 80); // 1->5
	node1.connect(&node6, 30); // 1->6
	node2.connect(&node4, 10); // 2->4
	node5.connect(&node6, 15); // 5->6

	GraphNode source(0); // source
	source.connect(&node1, INT_MAX);

	GraphNode sink(9);  // sink
	node2.connect(&sink, node2.getDemand());
	node3.connect(&sink, node3.getDemand());
	node4.connect(&sink, node4.getDemand());
	node5.connect(&sink, node5.getDemand());
	node6.connect(&sink, node6.getDemand());

	Graph graph({ source, sink, node1, node2, node3, node4, node5, node6 });

	// Passo 1
	auto data = Algorithms::EdmondKarp(&graph, &source, &sink);
	int maxFlow = data.first;
	BOOST_CHECK(maxFlow == 185);

	// Passo 2
	int totalDemand = 0;
	for (GraphNode node : graph.getNodes()) {
		if (node.getDemand() > 0) {
			totalDemand += node.getDemand();
		}
	}
	int unattendedEnergy = totalDemand - maxFlow;
	BOOST_CHECK(unattendedEnergy == 5);

	// Passo 3
	int totalOutgoingFlow = 0;
	for (GraphEdge& edge : node1.getEdges()) { // gerador
		totalOutgoingFlow += edge.getFlow();
	}
	BOOST_CHECK(totalOutgoingFlow == 105);

	// Passo 4
	std::vector<GraphEdge> criticalEdges;
	for (auto& node : graph.getNodes())
		for (auto& edge : node.getEdges()) {
			auto key = std::make_pair(node.getIndex(), edge.getTarget()->getIndex());
			if (edge.getCapacity() == data.second[key])
				criticalEdges.push_back(edge);
		}

	for (GraphEdge& edge : criticalEdges) {
		std::cout << edge.getSource()->getIndex() << " "
			<< edge.getTarget()->getIndex() << " "
			<< edge.getCapacity() << std::endl;
	}

	//BOOST_CHECK(criticalEdges.size() == 2);
	//BOOST_CHECK(*criticalEdges[0].getSource() == node1 && *criticalEdges[0].getTarget() == node6 && criticalEdges[0].getCapacity() == 30);
	//BOOST_CHECK(*criticalEdges[1].getSource() == node5 && *criticalEdges[1].getTarget() == node6 && criticalEdges[1].getCapacity() == 15);
}