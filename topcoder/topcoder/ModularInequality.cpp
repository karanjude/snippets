
#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <map>
#include <algorithm>

#include <utility.cpp>

using namespace std;

typedef long long LL;

class ModularInequality {
private:
	LL satisfied(vector<LL> a,LL x,LL p){
		LL sum = 0;
		for(LL i = 0;i < a.size();i++){
			sum += abs(a[i]);
		}
		
		return sum ;
	}
public: 
	int countSolutions(vector <LL> a, LL p){
		LL r = 0;
		LL sum = satisfied(a,0,p);
		r = (sum - p) / a.size();
		return r;
	}
};


int _tmain(int argc, _TCHAR* argv[]){
	LL i[] = {1, 2, 3};

	ModularInequality s;

	LL i1[] = {10, 30, 15, -1, 17};
	are_equal_with_print<double>(5,s.countSolutions(to_vector<LL,3>(i),6));
	are_equal_with_print<double>(7,s.countSolutions(to_vector<LL,5>(i1),42));

/*	{-693}
1265
Returns: 2531

		     
{965, -938, -396, -142, 926, 31, -720}
6495
Returns: 1781*/
	int ii;
	cin >> ii;
	return 0;
}