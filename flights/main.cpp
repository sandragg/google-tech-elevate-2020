#include <iostream>
#include <queue>
#include <algorithm>
#include "graph.h"


struct Flight
{
	std::string departs;
	std::string arrives;
	int price;
};

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

	graph::Graph graph;
	for (const auto &flight : flights)
		graph.AddEdge(flight.departs, flight.arrives, flight.price);

	auto connections = graph.FindShortestRoutes(source, destination, limit);
	if (connections.empty())
	{
		std::cout << "<no solution>";
		return 0;
	}

	for (const auto &connection : connections)
	{
		for (const auto &airport : connection.nodes)
			std::cout << airport << " ";
		std::cout << connection.cost << std::endl;
	}

	return 0;
}

/*

13
SFO JFK 500
JFK WAW 800
JFK BSL 700
JFK ZRH 700
ZRH BSL 300
SFO HEL 1000
SFO MUC 1100
SFO LHR 1100
MUC ZRH 500
LHR BSL 1
LHR ZRH 100
BSL ZRH 1
SFO ZRH 5000
10
SFO ZRH

 */