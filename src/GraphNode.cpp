#include "GraphNode.h"

GraphNode::GraphNode() : m_index(0) {}

GraphNode::GraphNode(std::size_t index) : m_index(index) {}

void GraphNode::connect(GraphNode* node) {
	m_edges.push_back(GraphEdge(this, node));
}

void GraphNode::disconnect(GraphNode* node) {
	m_edges.erase(std::remove(m_edges.begin(), m_edges.end(), GraphEdge(this, node)), m_edges.end());
}

bool GraphNode::isConnected(GraphNode* node) {
	for (GraphEdge& e : m_edges)
		if (*e.getTarget() == *node)
			return true;
	return false;
}

std::vector<GraphEdge>& GraphNode::getEdges() {
	return m_edges;
}

void GraphNode::setEdges(std::vector<GraphEdge> edges) { m_edges = edges; }

bool GraphNode::operator==(const GraphNode& other) const {
	return (m_index == other.getIndex());
}

bool GraphNode::operator<(const GraphNode& other) const {
	return this->m_index < other.getIndex();
}

std::size_t GraphNode::getIndex() const { return m_index; }