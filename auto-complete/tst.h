#ifndef TST_H
#define TST_H

#include <string>
#include <vector>
#include <stack>


/* Ternary search tree */
namespace tst
{

class Trie
{
		using position = int;

	public:
		Trie(size_t size = DEFAULT_SIZE);
		Trie& Insert(std::string str);
		Trie& Remove(std::string str);
//		std::vector<std::string> MatchPrefix(std::string prefix, size_t limit = 0) const;

	private:
		struct Node
		{
			char character;
			bool is_end;
			position left, mid, right;
			position next_free;
		};

		static const position END = -1;
		static const position DEFAULT_SIZE = 32;

		std::vector<Node> nodes;
		position root;
		size_t space_cursor;

		position allocate_node();
		void deallocate_node(position p);
		void init_space_cursor(position begin);
		void init_node(position p);
		position insert(position root_p, std::string str);
		position remove(position root_p, std::string str);
		position remove_path(position root_p, std::stack<position> &stack);
		bool empty_node(position p) const;
};

} // namespace tst


#endif //TST_H
