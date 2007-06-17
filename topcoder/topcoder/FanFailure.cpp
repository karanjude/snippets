#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <cctype>
#include <string>
#include <list>
#include <utility.cpp>

using namespace std;

class FanFailure{
	int min_x(vector<int> capacities , vector<int> req , int w){
		int min_val = 10000000;
		int index = 0;
		for(int i = 0; i < capacities.size();i++){
			if(!req[i]){
				if(w - capacities[i] < min_val){
					index = i;
					min_val = abs(w - capacities[i]);
				}
			}
		}
		return index;
	}

	int get_count(vector<int> r){
		int c = 0;
		for(int i = 0; i < r.size();i++)
			if(r[i]) c++;
		return c;
	}
public:
	vector<int> getRange(vector<int> capacities,int minCooling){
		sort(capacities.begin(),capacities.end(),greater<int>());
		vector<int> req(capacities.size(),0); 
		int w = minCooling;
		for(int i = 0;i < capacities.size() && w > 0;i++){
			int j = min_x(capacities,req,w);
			req[j] = 1;
			w -= capacities[j];
		}
		int r = get_count(req);
		int v = capacities.size() - r;
		vector<int> result;
		result.push_back(v);
		result.push_back(r);
		return result;
	}
};

int _tmain(int argc, _TCHAR* argv[]){

int i[] = {1,2,3};
int r[] = { 2,  1 };

FanFailure f;
are_equal(to_vector<int,2>(r),f.getRange(to_vector<int,3>(i),2));

int i1[] = {8,5,6,7};
int r1[] = { 0,  0 };
are_equal(to_vector<int,2>(r1),f.getRange(to_vector<int,4>(i1),22));

int i2[] = {676, 11, 223, 413, 823, 122, 547, 187, 28};
int r2[] = { 7,  2 };
are_equal(to_vector<int,2>(r2),f.getRange(to_vector<int,9>(i2),1000));

int i3[] = {955, 96, 161, 259, 642, 242, 772, 369, 311, 785,
 92, 991, 620, 394, 128, 774, 973, 94, 681, 771,
 916, 373, 523, 100, 220, 993, 472, 798, 132, 361,
 33, 362, 573, 624, 722, 520, 451, 231, 37, 921,
 408, 170, 303, 559, 866, 412, 339, 757, 822, 192};
int r3[] = { 46,  30 };
are_equal(to_vector<int,2>(r3),f.getRange(to_vector<int,50>(i3),3619));

	int ii;
	cin >> ii;
	return 0;
}