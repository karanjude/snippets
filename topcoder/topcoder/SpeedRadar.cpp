#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>

#include <utility.cpp>

using namespace std;

class SpeedRadar{
	bool is_more_than_ten_percent(int count , int n){
		return (double)count > (double)((double)n / (double)10);
	}

public:
	double averageSpeed(int minLimit, int maxLimit, vector <int> readings){
		int count = 0;
		int n = 0;
		int sum = 0;
		vector<int> other;
		for(int i = 0;i < readings.size();i++){
			int v = readings[i];
			if( (readings.at(i) < minLimit) || (readings.at(i) > maxLimit)){
				count++;
				other.push_back(readings[i]);
			}else{
				sum += readings[i];
				n++;
			}
		}
		if(is_more_than_ten_percent(count,readings.size()))
			return 0.0;
		return (double)sum  / (double)n;
	}
};

int _tmain(int argc, _TCHAR* argv[]){
	SpeedRadar s;

	int i[] = {45,40,50};
	are_equal_with_print<double>(45.0,s.averageSpeed(1,50,to_vector<int,3>(i)));

	int i1[] = {42,43,44,45,46,47,48,49,50,51};
	are_equal_with_print<double>(46.0,s.averageSpeed(1,50,to_vector<int,10>(i1)));
	
	int i2[] = {42,46,48,50,52};
	are_equal_with_print<double>(0.0,s.averageSpeed(1,50,to_vector<int,5>(i2)));

	int i3[] = {25,45,45,43,24,9,51,55,60,34,61,23,40,40,47,49,33,23,47,54,54};
	are_equal_with_print<double>(41.68421052631579,s.averageSpeed(20,60,to_vector<int,21>(i3)));

	
	int ii;
	cin >> ii;
	return 0;
}