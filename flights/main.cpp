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

void init_flights(std::istream &stream, std::vector<Flight> &flights)
{
	int number_of_flights;
	std::cin >> number_of_flights;

	flights.resize(number_of_flights);
	for (auto &flight : flights)
	{
		stream >> flight.departs;
		stream >> flight.arrives;
		stream >> flight.price;
	}
}

int main()
{
	std::vector<Flight> flights;
	init_flights(std::cin, flights);

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