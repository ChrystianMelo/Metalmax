#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <unordered_map>

#include "Graph.h"

/**
 * \class Algorithms
 *
 * \brief Algotimos aprendidos a partir do livro Algorithm Design de Jon Kleinberg
 */
class Algorithms {
public:
	/**
	 * \brief
	 *
	 * \details Complexidade =
	 */
	static int EdmondKarp(Graph* graph, GraphNode* source, GraphNode* sink);
};

#endif // ALGORITHMS_H
