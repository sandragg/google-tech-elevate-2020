#ifndef TST_H
#define TST_H

#include <string>
#include <vector>


/* Ternary search tree */
namespace tst
{

class Trie
{
		using position = int;

	public:
		Trie(size_t size = DEFAULT_SIZE);
		Trie& Insert();
		Trie& Remove();
		std::vector<std::string> MatchPrefix(std::string prefix, size_t limit = 0) const;

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

		void init_space_cursor(position begin);

};

} // namespace tst


#endif //TST_H
