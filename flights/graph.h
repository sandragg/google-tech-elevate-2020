#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include "route.h"


namespace graph
{

class Edge;

struct Node
{
	std::string code;
	std::unordered_map<std::string, Edge> connections;
	Node() = default;
	Node(std::string code);
	bool operator==(const Node &rhs) const;
};

struct Edge
{
	Node *node;
	int weight;
	Edge(int weight, Node &node);
};

class Graph
{
	public:
		Graph(size_t size = DEFAULT_SIZE);
		Graph& AddEdge(std::string src, std::string dest, int weight);
		std::vector<Route> FindRoutes(std::string src, std::string dest) const;

	private:
		static const size_t DEFAULT_SIZE = 32;
		std::unordered_map<std::string, Node> nodes;
};

} // namespace graph


#endif //GRAPH_H
