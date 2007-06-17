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
static int _connected[30][30];


class Marketing {
private :
	int vert_count ;
	vector<int> visited;
	map<int , vector<int>> connectedMap;
public:

	void buildMatrices(vector<string> compete){
		for(int i = 0;i < compete.size() ; i++){
			istringstream iss(compete[i]);
			int val = 0;
			while(iss >> val){
				_compete[i][val] = 0;
				_connected[i][val] = 1;
			}
		}
	}

	void buildConnectedMap(int connectedTo , int connectedBy ){
		if( connectedMap.find(connectedTo) == connectedMap.end())
			connectedMap[connectedTo] = vector<int>();
		vector<int> & v = connectedMap[connectedTo];
		if(find(v.begin(),v.end(),connectedBy) != v.end())
			return ;
		else
			v.push_back(connectedBy);
		for(int i = 0; i < vert_count;i++){
			if(_connected[connectedBy][i])	
				buildConnectedMap(connectedTo,i);
		}
	}

	bool canBeReached(int to , int by){
		vector<int> v = connectedMap[to];
		return (find(v.begin(),v.end(),by) != v.end());
	}

	void init_stuff(){
		vert_count = 0;
		memset(_connected,0,sizeof(_connected));
		memset(_compete,1,sizeof(_compete));
	}

	void find_path(int vx , string path , int count ){
		visited[vx] = 1;
		path += to_string<int>(vx);
			for(int i = 0;i < vert_count ; i++){
				if(_compete[vx][i] && !visited[i] && !canBeReached(vx,i)){
					find_path(i,path + "-" , count + 1);
				}
			}
	    if(count == vert_count) 
			cout << endl << path;
		visited[vx] = 0;
	}

	long howMany(vector<string> compete){
		init_stuff();
		buildMatrices(compete);
		vert_count = compete.size();
		for(int i = 0; i < vert_count ; i++){
			for(int j = 0; j < vert_count;j++){
				if(_connected[i][j])
					buildConnectedMap(i,j);
			}
		}

		
		vector<int> v(vert_count);
		visited = v;

		for(int i = 0; i < vert_count ; i++){
			find_path(i, "" , 1);
		}
		return 0;
	}
};



/*

int _tmain(int argc, _TCHAR* argv[])
{
	int i ;

	string compete[] = {"1 4",
            "2",
            "3",
            "0",
	    ""};

	
	Marketing m;
	m.howMany(to_vector<string , 5>(compete));

	cout << endl << endl ;

	string compete1[] = {"1","2","0"};

	m.howMany(to_vector<string , 3>(compete1));


	cin >> i;
}
*/