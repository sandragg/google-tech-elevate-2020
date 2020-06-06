#include "tst.h"


namespace tst
{

Trie::Trie(size_t size)
{
	nodes.resize(size);
	init_space_cursor(0);
	root = space_cursor;
}

void Trie::init_space_cursor(position begin)
{
	space_cursor = begin;

	for (size_t i = begin; i < nodes.size(); i++)
		nodes[i].next_free = i + 1;
}

} // namespace tst
