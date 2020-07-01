#include "graph.h"
#include <unordered_map>


namespace graph
{

Node::Node(std::string code)
{
	this->code = code;
}

bool Node::operator==(const Node &rhs) const
{
	return code == rhs.code;
}

Edge::Edge(int weight, Node &node)
{
	this->weight = weight;
	this->node = &node;
}

bool Graph::RouteWithMeta::operator>(const RouteWithMeta &rhs) const
{
	return route > rhs.route;
}

Graph& Graph::AddEdge(std::string src, std::string dest, int weight)
{
	nodes.emplace(src, Node(src));

	auto [ iterator, success ] = nodes.emplace(dest, Node(dest));
	Edge edge(weight, iterator->second);

	nodes[src].connections.emplace(dest, edge);

	return *this;
}

std::vector<Route> Graph::FindShortestRoutes(std::string src, std::string dest, size_t limit) const
{
	if (!nodes.count(src) || !nodes.count(dest) || !limit) return {};

	std::priority_queue<
		Route,
		std::vector<Route>,
		std::greater<>> routes;
	find_routes(src, dest, routes, limit);

	std::vector<graph::Route> result(std::min(limit, routes.size()));
	for (auto &route : result)
	{
		route = routes.top();
		routes.pop();
	}

	return result;
}

template <class Container, class Comparator>
void Graph::find_routes(
	const std::string &src,
	const std::string &dest,
	std::priority_queue<Route, Container, Comparator> &routes,
	size_t limit) const
{
	std::priority_queue<
		RouteWithMeta,
		std::vector<RouteWithMeta>,
		Comparator> queue;
	Route route = { { src }, 0 };
	std::unordered_set<std::string> visited_nodes;
	queue.push(RouteWithMeta{ route, visited_nodes });

	while (!queue.empty() && limit)
	{
		auto route_with_meta = queue.top();
		auto curr_node_code = route_with_meta.route.nodes.back();
		queue.pop();

		if (curr_node_code == dest)
		{
			routes.push(route_with_meta.route);
			limit--;
			continue;
		}
		process_node(route_with_meta, queue);
	}
}

template <class Container, class Comparator>
void Graph::process_node(
	const RouteWithMeta &route_with_meta,
	std::priority_queue<RouteWithMeta, Container, Comparator> &queue) const
{
	auto node_code = route_with_meta.route.nodes.back();
	auto node = nodes.at(node_code);
	auto visited_nodes = route_with_meta.visited_nodes;

	if (visited_nodes.count(node_code)) return;

	visited_nodes.insert(node_code);
	for (const auto &[ code, edge ] : node.connections)
	{
		auto next_route = route_with_meta.route;
		next_route.cost += edge.weight;
		next_route.nodes.push_back(code);
		queue.push(RouteWithMeta{ next_route, visited_nodes });
	}
}

} // namespace graph
