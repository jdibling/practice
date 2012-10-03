#include <cstdlib>
#include <string>

namespace bst
{
	struct Node
	{
		std::string val_;
		Node		*parent_,
					*left_,
					*right_;

	};
	struct BST
	{
		BST() : root_(0) {}
		Node*	root_;
		Node*	insert(const std::string& val);
		Node*	search(const std::string& val);
		void	print();
		Node*	get_max();
		Node*	get_min();

	};

};