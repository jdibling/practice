#include <cstdlib>
#include <string>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

#include "st.h"

struct node
{
	string 			suffix_;
	size_t 			i_;
	vector<node> 	child_;
};

void st(const char* text)
{
}
