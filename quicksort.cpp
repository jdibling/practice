#include <cstdlib>
#include "quicksort.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;

template<class V> bool is_sorted(V ary[])
{
	V prev = ary[0];
	for( size_t i = 1; i < sizeof(ary); ++i )
	{
		if( ary[i] < prev )
			return false;
		prev = ary[i];
	}

	return true;
}

struct Part
{
	size_t left_, right_;
	Part* next_;
	static uint64_t inst_;
	Part() { ++inst_; }
	virtual ~Part() { --inst_; }
};

uint64_t Part::inst_ = 0;

void quicksort_1(const size_t N)
{
	unsigned* ary = new unsigned[N];
	srand((unsigned)time(0));
	for( size_t i = 0; i < N; ++i )
		ary[i] = (unsigned)rand()/(RAND_MAX/1000);

	cout << "quicksorting " << N << " elements..." << endl;

	///*** PARTITION THE ARRAY ***///
	Part* root = new Part;
	root->left_ = 0;
	root->right_ = N-1;
	root->next_ = 0;

	for( Part* cur = root; cur; )
	{
		// set up the partition
		size_t left_i = cur->left_, right_i = cur->right_;
		size_t p_i = ((right_i-left_i+1)/2)+left_i;	// pivot at center
		unsigned pivot = ary[p_i];
		swap(ary[p_i],ary[right_i]);	// move pivot to right end
		p_i = right_i; 

		// do the partition
		size_t ins_i = left_i;
		for( size_t i = left_i; i <= (right_i-1); ++i )
		{
			if( ary[i] < pivot )
			{
				// move this one to the insertion point
				swap(ary[i], ary[ins_i]);
				++ins_i;
			}
		}

		// move pivot to insertion point
		swap(ary[p_i], ary[ins_i]);
		
		// partition done
		//cout << "[" << left_i << "-" << right_i << " - P=" << pivot << "]" << endl;
		//copy(&ary[left_i], &ary[right_i+1],ostream_iterator<unsigned>(cout, " "));
		//cout << endl;

		// set up next partitions
		if( (ins_i-left_i) > 1 )
		{
			Part* x = new Part;
			x->next_ = cur->next_;
			cur->next_ = x;
			x->left_ = left_i;
			x->right_ = ins_i-1;
		}
		if( (right_i-ins_i) > 1 )
		{
			Part* x = new Part;
			x->next_ = cur->next_;
			cur->next_ = x;
			x->left_ = ins_i + 1;
			x->right_ = right_i;
		}

		Part* tmp = cur;
		cur = cur->next_;
		delete tmp;
	}

	if( is_sorted(ary) )
		cout << "Sort OK" << endl;
	else
	{
		cout << "Sort FAIL! " << endl;
		//copy(&ary[0], &ary[N], ostream_iterator<unsigned>(cout, " "));
	}

	cout << "Part instances remaining: " << Part::inst_ << endl;
	delete ary;
	cout << "DONE." << endl;
}
