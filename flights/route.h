#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <vector>


namespace graph
{

struct Route
{
	std::vector<std::string> nodes;
	int cost;

	bool operator>(const Route& rhs) const;
};

} // namespace graph


#endif //ROUTE_H
