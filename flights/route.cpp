#include "route.h"


namespace graph
{

bool Route::operator>(const Route& rhs) const
{
	if (cost != rhs.cost)
		return cost > rhs.cost;

	if (nodes.size() != rhs.nodes.size())
		return nodes.size() > rhs.nodes.size();

	return nodes > rhs.nodes;
}

} // namespace graph
