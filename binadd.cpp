#include <cstdlib>
#include <string>
#include <iostream>
#include <iterator>
using namespace std;

#include "binadd.h"

int bin_add(int a, int b)
{
	/*
	 * 				  0  1  1  0  1  0  1
	 * 				  1  1  0  0  0  1  0
	 * 				----------------------
	 *  AND 		  0  1  0  0  0  0  0 		carry (<<1)
	 *  XOR 		  1  0  1  0  1  1  1		sum
	 *  		--------------------------------
	 *  carry  	   0  1  0  0  0  0  0  0      
	 *  sum    	   0  1  0  1  0  1  1  1
	 *  		--------------------------
	 *  AND        0  1  0  0  0  0  0  0		carry (<<1)
	 *  XOR        0  0  0  1  0  1  1  1       sum
	 *      ---------------------------------
	 *  carry   0  1  0  0  0  0  0  0  0
	 *  sum		0  0  0  0  1  0  1  1  1
	 *  		--------------------------
	 *  AND	    0  0  0  0  0  0  0  0  0            
	 *  XOR     0  1  0  0  1  0  1  1  1            
	 *  	---------------------------------
	 *answer    0  1  0  0  1  0  1  1  1
	 */

	int sum = a, carry = b;
	while( carry > 0 )
	{
		int and_v = sum&carry;
		int xor_v = sum^carry;

		sum = xor_v;
		carry = (and_v<<1);
	}

	return sum;
}

