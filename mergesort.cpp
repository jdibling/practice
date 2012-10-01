#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
using namespace std;

template<class V> bool is_sorted(V* ary, size_t N)
{
	V prev = ary[0];
	for( size_t i = 1; i < N; ++i )
	{
		if( ary[i] < prev )
			return false;
	}

	return true;
}

template<class V> void merge(V* ary, size_t left_i, size_t left_n, size_t right_n)
{
	size_t init_ary_i = left_i;

	size_t merge_n = left_n + right_n;
	V * result = new V[merge_n];

	size_t right_i = left_i + left_n;

	for( size_t result_i = 0; (left_n+right_n) > 0; result_i++ )
	{
		if( left_n > 0 && right_n > 0 )
		{
			if( ary[left_i] < ary[right_i] )
			{
				result[result_i] = ary[left_i];
				--left_n;
				++left_i;
			}
			else
			{
				result[result_i] = ary[right_i];
				--right_n;
				++right_i;
			}
		}
		else if( left_n > 0 )
		{
			result[result_i] = ary[left_i];
			--left_n;
			++left_i;
		}
		else if( right_n > 0 )
		{
			result[result_i] = ary[right_i];
			--right_n;
			++right_i;
		}
		else
			throw(string("Internal Error"));


	}
	
	for( size_t r_i = 0, a_i = init_ary_i; r_i < merge_n; ++ r_i, ++a_i )
		ary[a_i] = result[r_i];

	delete result;
}

bool mergesort_1(const size_t N)
{
	unsigned* ary = new unsigned[N];
	srand((unsigned)time(0));
	for( size_t i = 0; i < N; ++i )
		ary[i] = (unsigned)rand()/(RAND_MAX/10);

	for( size_t block_size = 1; block_size <= N; block_size*=2 )
	{
		for( size_t left_i = 0; left_i < N; left_i += (block_size*2) )
		{
/*
                        1 1 1
 	0 1 2 3 4 5 6 7 8 9 0 1 2      N = 13
	n n n n n n n n n n n n n
 	L L L L R R R R L L L L R     block_size = 4
                  a_b = 8
				  a_e = min(a_b+block_size,N)
				  b_l = a_e
				  b_r = min(b_b+block_size,N)
*/
			size_t l_b = left_i;
			size_t l_e = min(l_b+block_size, N);
			size_t r_b = l_e;
			size_t r_e = min(r_b+block_size, N);

			size_t l_n = l_e-l_b;
			size_t r_n = r_e-r_b;

			merge(ary, l_b, l_n, r_n);
		
		}
	}

	if( is_sorted(ary, N) )
	{
		//cout << "Sort OK" << endl;
		return true;
	}
	else
	{
		//cout << "Sort FAIL" << endl;
		return false;
	}


 }
