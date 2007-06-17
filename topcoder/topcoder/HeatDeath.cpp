#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>
#include <list>
#include <string>
#include <cctype>
#include <string>
#include <utility.cpp>
#include <cmath> 
#include <cstdlib>

using namespace std;
int n ;
int foo[100];

int int_comp( const void *a, const void *b ) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y)
  return 1;
    else if (x > y)
  return -1;
    else
  return 0;
}


class HeatDeath{
	
	bool closed(vector<int> energy){
		bool _closed = true;
		int n = energy.size();
		for(int i = 0;i < n;i++){
			for(int j = 0;j < n;j++){
				if(i == j) continue;
				if(energy[i] > energy[j] && energy[i]-energy[j] >= 2){
					_closed = false;
					return _closed;
				}
			}
		}
		return _closed;
	}

	int maxTime(vector<int> energy,int _total_energy){
		sort(energy.begin(),energy.end(),greater<int>());
		int max_energy = _total_energy;
		int total_energy = _total_energy;
		int n = energy.size();
			for(int i = 0; i < n-1;i++){
				for(int j = i+1;j < n;j++){
					if(i == j) continue;
					if(energy[i] > energy[j] && energy[i]-energy[j] >= 2){
							total_energy += 1;
							energy[i] -= 1;
							energy[j] += 1;
							max_energy = max(total_energy,max_energy);
						}
				}
			}
		return max_energy;
	}

public:
	int maxTime(vector<int> energy){
		return maxTime(energy,0);
	}
};


int _tmain(int argc, _TCHAR* argv[]){
	
	HeatDeath h;

	int ii0[] = {0,2};
	are_equal_with_print<int>(1,h.maxTime(to_vector<int,2>(ii0)));
	
	int ii1[] = {0,4};
	are_equal_with_print<int>(2,h.maxTime(to_vector<int,2>(ii1)));
	
	int i[] = { 5, 7, 9 };
	are_equal_with_print<int>(3,h.maxTime(to_vector<int,3>(i)));

	int i1[] = { 5, 6, 5 , 6 };
	are_equal_with_print<int>(0,h.maxTime(to_vector<int,4>(i1)));

	int i2[] = { 1, 1, 1, 1, 1, 999, 999, 999, 999, 999 };
	are_equal_with_print<int>(12435,h.maxTime(to_vector<int,10>(i2)));

	int ii;
	cin >> ii;
	return 0;
}