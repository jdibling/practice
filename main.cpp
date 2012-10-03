#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

#include "quicksort.h"
#include "mergesort.h"
#include "binadd.h"
#include "trie.h"
#include "bst.h"
int main()
{
	quicksort_1(100001);	

	for( size_t i = 1000000; i < 1000001; ++i )
	{
		if( !mergesort_1(i) )
		{
			cout << "Sort FAIL!" << endl;
		}
	}

	for( int i = 0; i < 0xFF; ++i )
	{
		for( int j = 0; j < 0xff; ++j )
		{
			int k = bin_add(i,j);
			if( k != (i+j) )
			{
				cout << "bin_add FAIL! bin_add(" << i << ", " << j << ") returned " << k << ", actually is " << (i+j) << endl;
			}
		}
	}

//	trie();

	bst::BST* bst = new bst::BST;
	bst->insert("hello");
	bst->insert("hell");
	bst->insert("hella");
	bst->insert("bye");
	bst->insert("zebra");

	cout << "In-Order Traversal: " << endl;
	bst->print();

	cout << "Max: " << bst->get_max()->val_ << "\tMin:" << bst->get_min()->val_ << endl;

}

