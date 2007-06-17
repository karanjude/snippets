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

using namespace std;

class Crossroads{
public:
	vector<int> getOut(vector<int> angles){
		int n = angles.size();
		vector<bool> pass(angles.size(),true);
		for(int i = 0;i < n-1;i++){
			for(int j = i+1;j < n;j++){
				if(angles[i] < angles[j]){
					if(abs(angles[i]-90) < abs(angles[j]-90))
						pass[j] = false;
					else if(abs(angles[i]-90) > abs(angles[j]-90))
							pass[i] = false;
						else
							pass[j] = false;
				}
			}
		}
		
		vector<int> result;
		for(int i = 0;i < n;i++)
			if(pass[i])
				result.push_back(i);
		return result;
	}
};

int _tmain(int argc, _TCHAR* argv[]){

	int i[] ={105, 75, 25, 120, 35, 75};
	int r[] = { 0,  1,  5 };
	Crossroads c;
	are_equal(to_vector<int,3>(r),c.getOut(to_vector<int,6>(i)));
	
	int i1[] = {1, 1, 1, 1, 1, 1};
	int r1[] = { 0,  1,  2,  3,  4,  5 };
	are_equal(to_vector<int,6>(r1),c.getOut(to_vector<int,6>(i1)));

	int i2[] = {13};
	int r2[] = { 0 };
	are_equal(to_vector<int,1>(r2),c.getOut(to_vector<int,1>(i2)));

	int i3[] = {90, 123, 1, 23, 132, 11, 28, 179, 179, 77, 113, 91};
	int r3[] = {0};
	are_equal(to_vector<int,1>(r3),c.getOut(to_vector<int,12>(i3)));

	int i4[] = {179, 89, 90, 91, 1};
	int r4[] = { 0,  2,  4 };
	are_equal(to_vector<int,3>(r4),c.getOut(to_vector<int,5>(i4)));

	int i5[] = {89 , 91};
	int r5[] = {0};
	are_equal(to_vector<int,1>(r5),c.getOut(to_vector<int,2>(i5)));

	int i6[] = {140, 118, 54, 166, 151, 44, 90, 5, 14, 6,
 64, 129, 74, 33, 134, 25, 11, 95, 65, 145,
 29, 162, 24, 147, 45, 103, 63, 97, 120, 156,
 167, 170, 19, 28, 100, 144, 161, 13, 157, 148};
	int r6[] =  { 0,  1,  6 };
	are_equal(to_vector<int,3>(r6),c.getOut(to_vector<int,40>(i6)));

	int ii;
	cin >> ii;
	return 0;
}