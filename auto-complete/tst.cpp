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

std::vector<std::string> Trie::GetAll() const
{
	std::vector<std::string> result;
	get_words(root, "", result, nodes.size());
	return result;
}

std::vector<std::string> Trie::MatchPrefix(std::string query_prefix, size_t limit) const
{
	std::vector<std::string> result;
	std::stack<position> stack;
	position node_p = root;
	std::string prefix;
	size_t prefix_index = 0;
	int typo_index = -1;

	if (query_prefix.empty())
	{
		get_words(root, query_prefix, result, limit);
		return result;
	}

	do {
		auto subtrie = get_prefix_subtrie(node_p, stack, query_prefix, prefix, prefix_index, typo_index);
		if (subtrie == END) break;

		auto &node = nodes[subtrie];
		if (node.is_end) result.emplace_back(prefix);

		get_words(node.mid, prefix, result, limit);
		node_p = pop_path(node.mid, prefix_index, stack);
		prefix.resize(prefix_index);
		if (typo_index >= prefix_index) typo_index = -1;
	} while (!stack.empty() && result.size() < limit);

	return result;
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
			if (node.mid == END || i == size) break;
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
			p = nodes[p].left = allocate_node();
		}
		else
		{
			if (node.right != END)
			{
				p = node.right;
				continue;
			}
			p = nodes[p].right = allocate_node();
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

Trie::position Trie::get_prefix_subtrie(
	position node_p,
	std::stack<position> &stack,
	const std::string& query_prefix,
	std::string& prefix,
	size_t &prefix_index,
	int &typo_index) const
{
	while (prefix_index < query_prefix.size() && (!stack.empty() || node_p != END))
	{
		if (stack.empty() || (node_p != stack.top() && node_p != nodes[stack.top()].left))
		{
			while (node_p != END)
			{
				stack.push(node_p);
				node_p = nodes[node_p].left;
			}
		}

		auto &node = nodes[stack.top()];

		if (node_p != END && node_p != node.left)
		{
			node_p = pop_path(node.mid, prefix_index, stack);
			if (typo_index >= prefix_index) typo_index = -1;
			prefix.resize(prefix_index);
			continue;
		}

		auto c = query_prefix[prefix_index];
		node_p = stack.top();

		if (node.character == c || typo_index < 0)
		{
			if (node.character != c) typo_index = prefix_index;
			if (node.mid != END) node_p = node.mid;
			prefix_index++;
			prefix.push_back(node.character);
			continue;
		}
		if (node.right == END)
		{
			stack.pop();
			node_p = pop_path(node_p, prefix_index, stack);
			prefix.resize(prefix_index);
		}
		else
		{
			node_p = node.right;
		}
		if (typo_index >= prefix_index) typo_index = -1;
	}

	return stack.empty() ? END : stack.top();
}

void Trie::get_words(
	Trie::position node_p,
	std::string prefix,
	std::vector<std::string>& result,
	size_t limit) const
{
	std::stack<position> stack;

	while (result.size() < limit && (!stack.empty() || node_p != END))
	{
		if (stack.empty() || node_p != nodes[stack.top()].left)
		{
			while (node_p != END)
			{
				stack.push(node_p);
				node_p = nodes[node_p].left;
			}
		}

		auto &node = nodes[stack.top()];
		prefix.push_back(node.character);

		if (node.is_end)
		{
			result.emplace_back(prefix);
		}
		if (node.mid != END)
		{
			node_p = node.mid;
		}
		else
		{
			auto prefix_new_size = prefix.size();
			node_p = pop_path(END, prefix_new_size, stack);
			prefix.resize(prefix_new_size);
		}
	}
}

Trie::position Trie::pop_path(Trie::position p, size_t &prefix_index, std::stack<position>& stack) const
{
	while (!stack.empty())
	{
		auto &node = nodes[stack.top()];
		if (p == node.left && p != END) break;

		if (p == node.mid)
		{
			if (prefix_index > 0) prefix_index--;
			if (node.right != END) return node.right;
		}
		p = stack.top();
		stack.pop();
	}

	return stack.empty() ? END : p;
}


} // namespace tst
