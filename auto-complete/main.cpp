#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "tst.h"


void Solve(const std::vector<std::string> &dict, const std::vector<std::string> &queries)
{
	// Write your code here
}

int main()
{
	size_t dict_size;
	if (!(std::cin >> dict_size)) std::exit(EXIT_FAILURE);

	std::vector<std::string> dict(dict_size);
	for (size_t i = 0; i < dict_size; ++i)
	{
		std::string dict_word;
		if (!(std::cin >> dict_word)) std::exit(EXIT_FAILURE);
		dict.emplace_back(dict_word);
	}

	size_t query_size;
	if (!(std::cin >> query_size)) std::exit(EXIT_FAILURE);

	std::vector<std::string> queries(query_size);
	for (size_t i = 0; i < query_size; ++i)
	{
		std::string query;
		if (!(std::cin >> query)) std::exit(EXIT_FAILURE);
		queries.push_back(query);
	}

	Solve(dict, queries);

	return 0;
}
