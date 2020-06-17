#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <vector>


namespace graph
{

struct Route
{
	std::vector<std::string> airports;
	int price;

	bool operator<(const Route& rhs) const;
};

} // namespace graph


#endif //ROUTE_H
