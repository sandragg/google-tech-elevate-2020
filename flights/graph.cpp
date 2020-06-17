#include "graph.h"


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

Graph::Graph(size_t size)
{
	nodes.reserve(size);
}

Graph& Graph::AddEdge(std::string src, std::string dest, int weight)
{
	nodes.emplace(src, Node(src));

	auto [ iterator, success ] = nodes.emplace(dest, Node(dest));
	Edge edge(weight, iterator->second);

	nodes[src].connections.insert({ dest, edge });
}

std::vector<Route> Graph::FindRoutes(std::string src, std::string dest) const
{

}

} // namespace graph
