#include <cstdlib>
#include <string>
#include <stack>
#include <iostream>
#include <iomanip>
using namespace std;

#include "bst.h"

bst::Node* bst::BST::insert(const std::string& val)
{
	using namespace bst;

	// find insertion point
	Node** cur = &root_, *parent = 0;
	while( *cur )
	{
		if( val < (*cur)->val_ )
		{
			parent = *cur;
			cur = &((*cur)->left_);
		}
		else
		{
			parent = *cur;
			cur = &((*cur)->right_);
		}
	}

	*cur = new Node;
	(*cur)->val_ = val;
	(*cur)->left_ = (*cur)->right_ = 0;
	(*cur)->parent_ = parent;

	return *cur;
}

bst::Node* bst::BST::search(const std::string& val)
{
	return 0;
}

void bst::BST::print()
{
	stack<Node*> disc;
	Node* cur = root_;
	while( !disc.empty() || cur )
	{
		if( cur )
		{
			disc.push(cur);
			cur = cur->left_;
		}
		else
		{
			cur = disc.top();
			disc.pop();
			cout << cur->val_ << endl;
			cur = cur->right_;
		}
	}
}

bst::Node* bst::BST::get_min()
{
	Node* cur = root_;
	while( cur->left_ )
		cur = cur->left_;
	return cur;
}

bst::Node* bst::BST::get_max()
{
	Node* cur = root_;
	while( cur->right_ )
		cur = cur->right_;
	return cur;
}