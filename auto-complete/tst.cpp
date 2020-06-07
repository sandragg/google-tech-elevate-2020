#include "tst.h"


namespace tst
{

Trie::Trie(size_t size)
{
	nodes.resize(size);
	init_space_cursor(0);
	root = END;
}

Trie& Trie::Insert(std::string str)
{
	if (!str.empty()) root = insert(root, str);
	return *this;
}

Trie& Trie::Remove(std::string str)
{
	if (!str.empty()) root = remove(root, str);
	return *this;
}

void Trie::init_space_cursor(position begin)
{
	space_cursor = begin;

	for (size_t i = begin; i < nodes.size(); i++)
		nodes[i].next_free = i + 1;
}

void Trie::init_node(Trie::position p)
{
	auto &node = nodes[p];
	node.left = node.mid = node.right = END;
	node.is_end = false;
}

Trie::position Trie::allocate_node()
{
	if (space_cursor == nodes.size())
	{
		nodes.resize(nodes.size() * 2);
		init_space_cursor(space_cursor);
	}
	auto position = space_cursor;
	space_cursor = nodes[space_cursor].next_free;
	init_node(position);

	return position;
}

void Trie::deallocate_node(position p)
{
	nodes[p].next_free = space_cursor;
	space_cursor = p;
}

Trie::position Trie::insert(position root_p, std::string str)
{
	size_t i = 0, size = str.size();

	if (root_p == END)
	{
		root_p = allocate_node();
		nodes[root_p].character = str[i];
	}

	position p = root_p;
	while (i < size)
	{
		auto c = str[i];
		auto &node = nodes[p];
		if (node.character == c)
		{
			i++;
			if (node.mid == END) break;
			p = node.mid;
			continue;
		}
		if (node.character > c)
		{
			if (node.left != END)
			{
				p = node.left;
				continue;
			}
			p = node.left = allocate_node();
		}
		else
		{
			if (node.right != END)
			{
				p = node.right;
				continue;
			}
			p = node.right = allocate_node();
		}
		nodes[p].character = c;
		i++;
		break;
	}

	while (i < size)
	{
		p = nodes[p].mid = allocate_node();
		nodes[p].character = str[i];
		i++;
	}
	nodes[p].is_end = true;

	return root_p;
}

Trie::position Trie::remove(Trie::position root_p, std::string str)
{
	if (root_p == END) return root_p;

	std::stack<position> stack;
	position p = root_p;

	for (size_t i = 0; i < str.size();)
	{
		if (p == END) return root_p;

		auto c = str[i];
		auto &node = nodes[p];

		stack.push(p);
		if (node.character == c)
		{
			p = node.mid;
			i++;
			continue;
		}
		p = node.character > c ? node.left : node.right;
	}
	p = stack.top();
	if (!nodes[p].is_end) return root_p;

	nodes[p].is_end = false;
	root_p = remove_path(root_p, stack);

	return root_p;
}

Trie::position Trie::remove_path(position root_p, std::stack<position>& stack)
{
	position child_p = END;
	while (!stack.empty())
	{
		if (child_p != END)
		{
			auto &parent = nodes[stack.top()];
			if (parent.left == child_p) parent.left = END;
			else if (parent.mid == child_p) parent.mid = END;
			else parent.right = END;
		}
		child_p = stack.top();
		if (!empty_node(child_p)) break;
		stack.pop();
		deallocate_node(child_p);
	}
	if (stack.empty()) root_p = END;

	return root_p;
}

bool Trie::empty_node(position p) const
{
	auto &node = nodes[p];
	return !node.is_end && node.left == END && node.mid == END && node.right == END;
}

} // namespace tst
