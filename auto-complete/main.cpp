#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "tst.h"


void Solve(const tst::Trie &dict, const std::vector<std::string> &queries)
{
	auto count = 0;
	for (auto &query : queries)
	{
		auto start = std::chrono::high_resolution_clock::now();
		auto words = dict.MatchPrefix(query, 100);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Query index: " << count++ << std::endl;
		std::cout << "Query length: " << query.size() << std::endl;
		std::cout << "Query: " << query << std::endl;
		std::cout << "Elapsed time: " << elapsed.count() * 1000 << " ms" << std::endl;
		if (words.empty())
		{
			std::cout << "<no matches>" << std::endl;
			continue;
		}
		for (auto &word : words)
			std::cout << word << " ";
		std::cout << std::endl;
	}
}

int main()
{
	size_t dict_size;
	if (!(std::cin >> dict_size)) std::exit(EXIT_FAILURE);

	tst::Trie dict;
	for (size_t i = 0; i < dict_size; ++i)
	{
		std::string dict_word;
		if (!(std::cin >> dict_word)) std::exit(EXIT_FAILURE);
		auto start = std::chrono::high_resolution_clock::now();
		dict.Insert(dict_word);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Word index: " << i << std::endl;
		std::cout << "Word length: " << dict_word.size() << std::endl;
		std::cout << "Elapsed time: " << elapsed.count() * 1000 << " ms" << std::endl;
	}

	size_t query_size;
	if (!(std::cin >> query_size)) std::exit(EXIT_FAILURE);

	std::vector<std::string> queries;
	queries.reserve(query_size);
	for (size_t i = 0; i < query_size; ++i)
	{
		std::string query;
		if (!(std::cin >> query)) std::exit(EXIT_FAILURE);
		queries.push_back(query);
	}

	auto words = dict.GetAll();
	for (auto &word : words)
		std::cout << word << std::endl;
	std::cout << std::endl;

	Solve(dict, queries);

	return 0;
}

/**
36
app
apple
bicycle
bob
by
lol
sea
steam
stone
team
ts
sells
shells
book
booking
appstore
pineapple
pipe
people
pencil
approve
animal
an
seaside
seashell
snow
bootcamp
boots
biology
bio
bioinformatic
treasure
teacher
teach
taught
touch

19
bio
bruno
bip
ann
a
po
en
seen
ser
ooo
pin
boot
boat
touc
tauc
pen
lol
zz
tea

 */


