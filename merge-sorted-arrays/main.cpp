#include <iostream>
#include <vector>
#include "merge.h"

template <class Tp>
void init_input_arrays(std::istream &stream, std::vector<std::vector<Tp>> &arrays)
{
	int n;
	stream >> n;
	std::vector<size_t> array_lengths(n);
	for (int i = 0; i < n; i++)
	{
		stream >> array_lengths[i];
	}

	arrays.resize(n);
	for (int i = 0; i < n; i++)
	{
		auto& size = array_lengths[i];
		auto& array = arrays[i];

		array.reserve(size);
		for (int j = 0; j < size; j++)
		{
			int value;
			stream >> value;
			array.push_back(value);
		}
	}
}

int main() {
	std::vector<std::vector<int>> arrays;
	init_input_arrays(std::cin, arrays);

	std::vector<int> merged;
	merge(arrays, merged);

	for (int value : merged)
	{
		std::cout << value << " ";
	}
	std::cout << std::endl;

	return 0;
}
