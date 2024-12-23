#include "GraphEdge.h"
#include "GraphNode.h"

GraphEdge::GraphEdge(GraphNode* source, GraphNode* target) : GraphEdge(source, target, 0) {}

GraphEdge::GraphEdge(GraphNode* source, GraphNode* target, int weight) : 
	m_source(source), m_target(target), m_flow(weight), m_capacity(weight), m_reverse(nullptr) {}

GraphNode* GraphEdge::getSource() const {
	return m_source;
}

GraphNode* GraphEdge::getTarget() const {
	return m_target;
}

GraphEdge* GraphEdge::getReverse() {
	if (m_reverse == nullptr)
		m_reverse = new GraphEdge(m_target, m_source, 0);
	return m_reverse;
}

bool GraphEdge::operator==(const GraphEdge& other) const {
	return *m_source == *other.getSource() && *m_target == *other.getTarget();
}