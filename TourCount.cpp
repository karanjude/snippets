#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <map>
#include <queue>
#include <list>

#include <string>
#include <sstream>
#include <cctype>
#include <cmath>

#include "utility.cpp"

using namespace std;
using namespace my;

/*

Author : karan singh
Email : karan.jude@gmail.com

Problem Statement


You are given a directed graph g, and you must determine the number of distinct cycles in g that have length less than k. Since this number can be really big, return the answer modulo m. A cycle is a non-empty sequence of nodes (not necessarily distinct) in which there is an edge from each node to the next node, and an edge from the last node in the sequence to the first node. Two cycles are distinct if their sequences are not identical. See example 0 for further clarification.

g will be given as a String[] where the jth character of the ith element indicates whether there is an edge from node i to node j ('Y' means there is one, and 'N' means there is not).

Definition

Class:	TourCounting
Method:	countTours
Parameters:	String[], int, int
Returns:	int
Method signature:	int countTours(String[] g, int k, int m)
(be sure your method is public)


Notes
-	The answer modulo m means that you must return the remainder of dividing the result by m.

Constraints
-	g will have between 1 and 35 elements, inclusive.
-	Each element of g will have exactly N characters, where N is the number of elements in g.
-	Each character of each element of g will be 'Y' or 'N'.
-	The ith character of the ith element of g will be 'N'.
-	k will be between 1 and 1000000 (106), inclusive.
-	m will be between 1 and 1000000000 (109), inclusive.

Examples
0)


{"NYNY",
 "NNYN",
 "YNNN",
 "YNNN"}

6

100

Returns: 12

The possible cycles with length less than 6 are:

(0,3) ; (3,0) ; (0,1,2) ; (1,2,0) ; (2,0,1)

(0,3,0,3) ; (3,0,3,0) ; (0,1,2,0,3) ; (0,3,0,1,2)

(1,2,0,3,0) ; (2,0,3,0,1) ; (3,0,1,2,0)

Note that (0,3), (3,0) and (0,3,0,3) are all considered different.
1)


{"NYNNNNN",
 "NNYNNNN",
 "NNNYNNN",
 "NNNNYNN",
 "NNNNNYN",
 "NNNNNNY",
 "YNNNNNN"}

40

13

Returns: 9

All cycles have lengths that are multiples of 7. For each starting node and each multiple of 7 there exists one cycle. There are 5 non-zero multiples of 7 that are less than 40 (7,14,21,28,35) and 7 possible starting nodes. Therefore, the total number of cycles is 5x7=35. 35 modulo 13 is 9.
2)


{"NYNY",
 "NNNN",
 "YYNY",
 "NYNN"}

1000000

1000000000

Returns: 0

The graph does not have cycles.
3)


{"NY",
 "YN"}

1500

1

Returns: 0

Any number modulo 1 is zero.
4)


{"NYYNYYN",
 "YNYNYNY",
 "NYNYNYN",
 "YYYNYNY",
 "NNYYNNY",
 "NYYYNNY",
 "YYYYYYN"}

30

100

Returns: 72

5)


{"NYYY",
 "YNYY",
 "YYNY",
 "YNYN"}

1000

10000

Returns: 3564

logic :
This program asks for computation of all cycles of all possible in a graph modulo m
Given graph of order n and Adj(g(n)) then trace(Adj(g(n))) is equal to the all posiible cycles for
adj of graph of order n

Now to get all possible cycles all we need to do is add all calculate trace over all the possible
adj(n) where n = 0 to n-1

now in a graph the number of routes can be obtained by pow(Adj,k)

*/



class TourCounting{
public:
	vector< vector<int> > add(vector< vector<int> > & a , vector < vector<int> > & b ,int m,int n ){
		vector< vector<int> > result(n,vector<int>(n,0));
		for(int i =0;i < n;i++){
			for(int j = 0;j < n;j++){
				result[i][j] = (a[i][j] + b[i][j]) % m;
			}
		}
		return result;
	}

	vector< vector<int> > mul(vector< vector<int> > & a , vector < vector<int> > & b ,int m,int n){
		vector < vector<int> > v = zero(n);
		for(int i = 0;i < n;i++){
			for(int j = 0;j < n;j++){
				for(int k = 0;k < n;k++){
					v[i][j] = (v[i][j] + (a[i][k]*b[k][j])) % m;
				}
			}
		}
		return v;
	}

	// if k is even : pow(A,k) = pow(A,k/2) * pow(A,k/2)
	// if k is odd : pow(A,k) = pow(A,k-1) * A;
	vector< vector<int> > matrix_pow(vector< vector<int> > & a, int k,int m,int n){
		if(k == 0)
			return one(n);
		else if(k % 2 == 0){
			return matrix_pow(mul(a,a,m,n),k/2,m,n);
		}
		return mul(a,matrix_pow(a,k-1,m,n),m,n);
	}

	vector< vector<int> > zero(int n){
		vector < vector<int> >  r (n , vector<int>(n,0));
		return r;
	}

	vector< vector<int> >  one(int n){
		vector < vector<int> >  r(n,vector<int>(n,0));
		for(int i = 0;i < n;i++){
			r[i][i] = 1;
		}
		return r;
	}

	// if even sum_to(k) = sum_to(k/2) + sum_to(k/2) * pow(A,k/2)
	// if odd sum_to(k) = sum_to(k-1) + pow(A,k) or sum_to(k-1)*A + A
	vector< vector<int>> sum_to(vector< vector<int> > & v , int k, int m,int n){
		if(k == 0)
			return zero(n);
		else if(k % 2 == 0){
			vector< vector<int> > & p1 = sum_to(v,k/2,m,n);
			vector< vector<int> > & a_k_by_2 = matrix_pow(v,k/2,m,n);
			vector< vector<int> > & r = add(p1,mul(p1,a_k_by_2,m,n),m,n);
			return r;
		}
		vector< vector<int> > & a_k_minus_1 = sum_to(v,k-1,m,n);
		vector< vector<int> > & a_times_a_k_minus_1 = mul(v,a_k_minus_1,m,n);
		vector< vector<int> > & r = add(a_times_a_k_minus_1,v,m,n);
		return r;
	}

	int countTours(vector<string> g,int k,int m){
		int n = g.size();
		vector< vector<int> > adj(n,vector<int>(n,0));
		for(int i = 0;i < n ;i++){
			for(int j = 0;j < n;j++){
				if(g[i][j] == 'Y'){
					adj[i][j] = 1;
				}
			}
		}
		vector< vector<int> > & result = sum_to(adj,k-1,m,n);
		int sum = 0;
		for(int i = 0;i < n;i++){
			sum = (sum + result[i][i]) % m;
		}

		return sum;
	}
};


int main(){

	TourCounting t;
	string s[] = {"NYNY",
 "NNYN",
 "YNNN",
 "YNNN"};

	cout << t.countTours(to_vector<string,4>(s),6,100);


int number;
	cin >> number;
	return 0;
}