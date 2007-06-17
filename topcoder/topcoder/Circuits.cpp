#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

#include <utility.cpp>


using namespace std;

static int _connects[50][50];
static int _costs[50][50];

class Circuits {
(

private:
	vector<int> visited;
	int vert_count ;

public:
	void buildMatrices(vector<string> connects , vector<string> costs){
		vert_count = connects.size();
		for(int i = 0; i < connects.size(); i++)		{
			istringstream iss(connects[i]);
			istringstream isss(costs[i]);
			int val = 0;
			while(iss >> val){
				_connects[i][val] = 1;
				int cost ;
				isss >> cost;
				_costs[i][val] = cost;
			}
		}
	}

void init_stuff(){
		vert_count = 0;
		memset(_connects,0,50 * 50);
		memset(_costs,0,50*50);
	}


	int visit(int vx , int cost){
		int r = 0;
		if(cost >  r) r = cost;

		for(int j = 0; j < vert_count ; j++){
			if(_costs[vx][j] > 0){
				r = max(r, visit(j , cost + _costs[vx][j]));
			}
		}
		return r;
	}

	


	int howLong(vector<string> connects , vector<string> costs){
		init_stuff();
		buildMatrices(connects,costs);	
		vector<int> v(vert_count);
		visited = v;
		int result = 0;
		for(int i = 0; i < vert_count ; i++){
			result = max(result , visit(i , 0) ) ;
		}
		return result;
	}
};




/*int _tmain(int argc, _TCHAR* argv[])
{
	int i ;
	string connects[] = {"1 2", "2", ""};

	string costs[] = {"5 3", "7", ""};
    
	Circuits cc;
	int result = cc.howLong( to_vector<string,3>(connects) , to_vector<string,3>(costs));
	are_equal_with_print<int>(12,result);

	string connects1[] = {"1 2 3 4 5","2 3 4 5","3 4 5","4 5","5",""};
 
	string costs1[] = {"2 2 2 2 2","2 2 2 2","2 2 2","2 2","2",""};
 
	result = cc.howLong( to_vector<string,6>(connects1) , to_vector<string,6>(costs1));

	are_equal_with_print<int>(10,result);	


 

 


	string connects2[] = {"1","2","3","","5","6","7",""};
 
	string costs2[] = {"2","2","2","","3","3","3",""};
 
	result = cc.howLong( to_vector<string,8>(connects2) , to_vector<string,8>(costs2));

	are_equal_with_print<int>(9,result);	




	
	string connects3[] = 	{"","2 3 5","4 5","5 6","7","7 8","8 9","10",
 "10 11 12","11","12","12",""};

 
	string costs3[] = 
	{"","3 2 9","2 4","6 9","3","1 2","1 2","5",
 "5 6 9","2","5","3",""};
 
	result = cc.howLong( to_vector<string,13>(connects3) , to_vector<string,13>(costs3));

	are_equal_with_print<int>(22,result);	

	string connects4[] = 	{"","2 3","3 4 5","4 6","5 6","7","5 7",""};

	string costs4[] = 
	{"","30 50","19 6 40","12 10","35 23","8","11 20",""};

 
	result = cc.howLong( to_vector<string,8>(connects4) , to_vector<string,8>(costs4));

	are_equal_with_print<int>(105,result);	


	cin >> i;
}
*/