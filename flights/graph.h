#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
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
		Graph& AddEdge(std::string src, std::string dest, int weight);
		std::vector<Route> FindShortestRoutes(std::string src, std::string dest, size_t limit) const;

	private:
		struct RouteWithMeta
		{
			Route route;
			std::unordered_set<std::string> visited_nodes;
			bool operator>(const RouteWithMeta &rhs) const;
		};

		std::unordered_map<std::string, Node> nodes;

		template <class Container, class Comparator>
		void find_routes(
			const std::string &src,
			const std::string &dest,
			std::priority_queue<Route, Container, Comparator> &result, size_t limit) const;

		template <class Container, class Comparator>
		void process_node(
			const RouteWithMeta &route,
			std::priority_queue<RouteWithMeta, Container, Comparator> &queue) const;
};

} // namespace graph


#endif //GRAPH_H
