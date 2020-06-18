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
		struct RouteWithMeta;
		using minimal_route_queue = std::priority_queue<Route, std::vector<Route>, std::greater<>>;
		using minimal_route_with_meta_queue = std::priority_queue<RouteWithMeta, std::vector<RouteWithMeta>, std::greater<>>;
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

		void find_routes(
			const std::string &src,
			const std::string &dest,
			minimal_route_queue &result, size_t limit) const;
		void process_node(
			const RouteWithMeta &route,
			minimal_route_with_meta_queue &queue) const;
};

} // namespace graph


#endif //GRAPH_H
