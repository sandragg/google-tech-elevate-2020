#include "merge.h"
#include <queue>
#include <algorithm>


struct HeapNode
{
	using source = const std::vector<int>;
	source* container;
	source::const_iterator element;

	bool operator>(const HeapNode& rhs) const
	{
		return *element > *rhs.element;
	}
};

template <class Container, class Comparator>
int get_min_and_advance(std::priority_queue<HeapNode, Container, Comparator>& heap)
{
	auto top = heap.top();
	const auto top_value = *top.element;

	heap.pop();
	top.element++;
	if (top.element != top.container->end()) heap.push(top);

	return top_value;
}

void merge(const std::vector<std::vector<int>>& input, std::vector<int>& output)
{
	std::priority_queue<
		HeapNode,
		std::vector<HeapNode>,
		std::greater<>
	> heap;

	for (const auto& container : input)
	{
		if (container.empty()) continue;
		heap.push({ &container, container.begin() });
	}

	while (!heap.empty())
	{
		auto min_value = get_min_and_advance(heap);
		output.push_back(min_value);
	}
}
