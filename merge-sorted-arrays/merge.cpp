#include "merge.h"
#include <queue>
#include <algorithm>

template <class Tp>
struct HeapNode
{
	using source = const std::vector<Tp>;
	source *container;
	typename source::const_iterator element;

	bool operator>(const HeapNode& rhs) const
	{
		return *element > *rhs.element;
	}
};

template <class Tp, class Container, class Comparator>
int get_min_and_advance(std::priority_queue<HeapNode<Tp>, Container, Comparator>& heap)
{
	auto top = heap.top();
	const auto top_value = *top.element;

	heap.pop();
	top.element++;
	if (top.element != top.container->end()) heap.push(top);

	return top_value;
}

template <class Tp>
void merge(const std::vector<std::vector<Tp>>& input, std::vector<Tp>& output)
{
	std::priority_queue<
		HeapNode<Tp>,
		std::vector<HeapNode<Tp>>,
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
