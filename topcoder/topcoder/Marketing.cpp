#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <map>

#include <utility.cpp>


using namespace std;

static int _compete[30][30];

class Marketing {
private :
	int vert_count ;
	vector<int> visited;
	bool error ;
public:

	void buildMatrices(vector<string> compete){
		for(int i = 0;i < compete.size() ; i++){
			istringstream iss(compete[i]);
			int val = 0;
			while(iss >> val){
				_compete[i][val] = 1;
				_compete[val][i] = 1;
			}
		}
	}

	void init_stuff(){
		vert_count = 0;
		error = false;
		memset(_compete,0,sizeof(_compete));
	}

	void find_path(int vx , string path ,int count , int color ){
		if(visited[vx] != 0 ) {
			if(visited[vx] != color) error = true;		
			return;
		}
		visited[vx] = color;
		path += to_string<int>(vx);
		
			cout << endl << path;
			for(int i = 0;i < vert_count ; i++){
					if(_compete[vx][i]){
					find_path(i,path + "-" , count + 1,3 - color);
				}
			}

	}

	long howMany(vector<string> compete){
		init_stuff();
		buildMatrices(compete);
		vert_count = compete.size();

		vector<int> v(vert_count);
		visited = v;

		long result = 1;
		for(int i = 0; i < vert_count ; i++){
			if(visited[i] == 0){
				find_path(i, "" , 1,1);
				if(error) return -1;
				result *= 2;
			}
		}
		return result;
	}
};






/* int _tmain(int argc, _TCHAR* argv[])
{
	int i ;

	string compete[] = {"1 4",
            "2",
            "3",
            "0",
	    ""};

	
	Marketing m;
	long result = m.howMany(to_vector<string , 5>(compete));

	are_equal_with_print<int>(2,result);

	cout << endl << endl ;


	string compete1[] = {"1","2","0"};

	result = m.howMany(to_vector<string , 3>(compete1));

	are_equal_with_print<int>(-1,result);


	string compete2[] = {"1","2","3","0","0 5","1"};

	result = m.howMany(to_vector<string , 6>(compete2));

	are_equal_with_print<int>(2,result);


	string compete3[] = {"","","","","","","","","","",
 "","","","","","","","","","",
 "","","","","","","","","",""};


	result = m.howMany(to_vector<string , 30>(compete3));

	are_equal_with_print<int>(1073741824,result);

string compete4[] = {"1","2","3","0","5","6","4"};


	result = m.howMany(to_vector<string , 7>(compete4));

	are_equal_with_print<int>(-1,result);



	cin >> i;
}
*/