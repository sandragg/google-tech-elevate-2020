#include <iostream>
#include <queue>
#include <algorithm>
#include "route.h"
#include "graph.h"


struct Flight
{
	std::string departs;
	std::string arrives;
	int price;
};

std::vector<graph::Route> find_connections(
	const std::vector<Flight> &flights,
	const std::string &start,
	const std::string &end,
	int limit)
{
	graph::Graph graph;

	for (const auto &flight : flights)
		graph.AddEdge(flight.departs, flight.arrives, flight.price);

	auto routes = graph.FindRoutes(start, end);
	std::make_heap(routes.begin(), routes.end());

	if (routes.size() <= limit)
	{
		std::sort(routes.begin(), routes.end());
		return routes;
	}

	std::vector<graph::Route> result(limit);
	for (auto &route : result)
	{
		std::pop_heap(routes.begin(), routes.end());
		route = routes.back();
		routes.pop_back();
	}

	return result;
}

int main()
{
	int number_of_flights;
	std::cin >> number_of_flights;

	std::vector<Flight> flights(number_of_flights);
	for (auto &flight : flights)
	{
		std::cin >> flight.departs;
		std::cin >> flight.arrives;
		std::cin >> flight.price;
	}

	int limit;
	std::cin >> limit;
	std::string source;
	std::cin >> source;
	std::string destination;
	std::cin >> destination;

	std::vector<graph::Route> connections = find_connections(flights, source, destination, limit);
	for (const auto &connection : connections)
	{
		for (const auto &airport : connection.airports)
			std::cout << airport << " ";
		std::cout << connection.price << std::endl;
	}

	return 0;
}

/*

13
SFO JFK 500
JFK SFO 800
JFK BSL 700
JFK ZRH 850
ZRH BSL 300
SFO HEL 1000
SFO LHR 1100
BSL SFO 500
MUC ZRH 500
LHR BSL 1
LHR ZRH 100
BSL ZRH 1
SFO ZRH 5000
10
ZRH IST

 */