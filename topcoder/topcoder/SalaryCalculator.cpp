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



class SalaryCalculator {
private:
	
public: 
	double calcHours(int P1, int P2, int salary){
		double hrs ;
		double value = 200.0;
		if(P1 * value > salary)
			hrs = (double)salary / (double)P1;
		else if(P1 * value <= salary){
			int new_salary = salary - P1 * value;
			hrs = (double)new_salary / (double)P2;
			hrs += value;
		}
			
		return hrs;
		
	}
};

using namespace std;

int _tmain(int argc, _TCHAR* argv[]){
	SalaryCalculator s;
	are_equal_with_print<double>(100.0,s.calcHours(10,15,1000));
	are_equal_with_print<double>(266.6666666666667,s.calcHours(10,15,3000));
	are_equal_with_print<double>(980200.0,s.calcHours(100,1,1000000));
	are_equal_with_print<double>(42380.260869565216,s.calcHours(17,23,973546));
	are_equal_with_print<double>(148.0487804878049,s.calcHours(82,8,12140));
	int ii;
	cin >> ii;
	return 0;
}