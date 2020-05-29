#include <iostream>
#include <vector>
#include "./merge.h"


int main() {
	int n;
	std::cin >> n;
	std::vector<int> array_lengths(n);
	for (int i = 0; i < n; i++)
	{
		std::cin >> array_lengths[i];
	}
	std::vector<std::vector<int>> arrays(n);
	for (int i = 0; i < n; i++)
	{
		auto& size = array_lengths[i];
		auto& array = arrays[i];

		array.reserve(size);
		for (int j = 0; j < size; j++)
		{
			int value;
			std::cin >> value;
			array.push_back(value);
		}
	}

	std::vector<int> merged;
	merge(arrays, merged);

	for (int value : merged)
	{
		std::cout << value << " ";
	}
	std::cout << std::endl;

	return 0;
}
