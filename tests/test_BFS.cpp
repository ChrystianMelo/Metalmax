#include <boost/test/unit_test.hpp>
#include <unordered_set>
#include "Graph.h"
#include "GraphNode.h"
#include "Algorithms.h"

namespace {
    // Classe para coletar os nós visitados
    class VisitedNodeCollector : public NodeVisitor {
    public:
        VisitedNodeCollector() : visited_() {}

        void visit(GraphNode* node) override {
            visited_.insert(*node);
        }

        std::unordered_set<GraphNode> getVisited() const {
            return visited_;
        }

    private:
        std::unordered_set<GraphNode> visited_;
    };
}

// Teste BFS básico para verificar se todos os nós são visitados
BOOST_AUTO_TEST_CASE(BFS_VisitsAllVertices) {
    GraphNode node1(1), node2(2), node3(3), node4(4);

    node1.connect(&node2);
    node2.connect(&node3);
    node3.connect(&node4);

    Graph graph({ node1, node2, node3, node4 });

    VisitedNodeCollector nodeCollector;
    Algorithms::BFS(graph.getNodes(), &nodeCollector);
    auto visited = nodeCollector.getVisited();

    BOOST_CHECK(visited.find(node1) != visited.end());
    BOOST_CHECK(visited.find(node2) != visited.end());
    BOOST_CHECK(visited.find(node3) != visited.end());
    BOOST_CHECK(visited.find(node4) != visited.end());
}

// Teste BFS com um grafo desconexo
BOOST_AUTO_TEST_CASE(BFS_DisconnectedGraph) {
    GraphNode node1(1), node2(2), node3(3), node4(4), node5(5);

    node1.connect(&node2);
    node3.connect(&node4);

    Graph graph({ node1, node2, node3, node4, node5 });

    VisitedNodeCollector nodeCollector;
    Algorithms::BFS(graph.getNodes(), &nodeCollector);
    auto visited = nodeCollector.getVisited();

    BOOST_CHECK(visited.find(node1) != visited.end());
    BOOST_CHECK(visited.find(node2) != visited.end());
    BOOST_CHECK(visited.find(node3) != visited.end());
    BOOST_CHECK(visited.find(node4) != visited.end());
    BOOST_CHECK(visited.find(node5) != visited.end());
}

// Teste BFS com um grafo cíclico
BOOST_AUTO_TEST_CASE(BFS_CyclicGraph) {
    GraphNode node1(1), node2(2), node3(3), node4(4);

    node1.connect(&node2);
    node2.connect(&node3);
    node3.connect(&node4);
    node4.connect(&node1);

    Graph graph({ node1, node2, node3, node4 });

    VisitedNodeCollector nodeCollector;
    Algorithms::BFS(graph.getNodes(), &nodeCollector);
    auto visited = nodeCollector.getVisited();

    BOOST_CHECK(visited.find(node1) != visited.end());
    BOOST_CHECK(visited.find(node2) != visited.end());
    BOOST_CHECK(visited.find(node3) != visited.end());
    BOOST_CHECK(visited.find(node4) != visited.end());
}
