#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <unordered_map>

#include "Graph.h"

struct PairHash {
	std::size_t operator()(const std::pair<int, int>& p) const {
		// Exemplo simples de combinar dois hashes
		// para os ints (p.first e p.second)
		auto h1 = std::hash<int>{}(p.first);
		auto h2 = std::hash<int>{}(p.second);

		// "Combinar" os hashes em um só
		// (Exemplo: técnica proposta por boost::hash_combine)
		// 0x9e3779b97f4a7c15ULL é um "magic number" comum para dispersão
		std::size_t seed = 0;
		// Combina h1:
		seed ^= h1 + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
		// Combina h2:
		seed ^= h2 + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);

		return seed;
	}
};

/**
 * \class Algorithms
 *
 * \brief Algotimos aprendidos a partir do livro Algorithm Design de Jon Kleinberg
 */
class Algorithms {
public:
	/**
	 *
	 */
	static std::pair<int, std::unordered_map<std::pair<int,int>, int, PairHash>> EdmondKarp(Graph* graph, GraphNode* source, GraphNode* sink);
};

#endif // ALGORITHMS_H
