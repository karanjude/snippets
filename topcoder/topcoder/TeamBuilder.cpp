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

static int team_paths[50][50];

class TeamBuilder {
private:
	int n ;
	void initialize(){
		memset(team_paths,0,sizeof(team_paths));
	}

	bool can_reach_all(int vertex){
		for(int i = 0;i < n;i++){
			if(i == vertex) continue;
			if(team_paths[vertex][i] != 1)
				return false;
		}
		return true;
	}

	bool can_be_reached_by_all(int vertex){
		for(int i = 0;i < n;i++){
			if(i == vertex) continue;
			if(team_paths[i][vertex] != 1)
				return false;
		}
		return true;
	}
public: 
	vector<int> specialLocations(vector<string> paths){
		n = paths.size();		
		initialize();
		for(int i = 0;i < n;i++){
				for(int j  =0;j < n; j++){
					int v = paths[i][j];
					if(v == '1')
						team_paths[i][j] = 1;
				}
			}

		//print_matrix<int,50,7>(team_paths);

		for(int k = 0;k < n;k++)
			for(int i = 0 ;i < n;i++)
				for(int j = 0;j < n;j++){
					if(team_paths[i][k] && team_paths[k][j])
						team_paths[i][j] = 1;
				}

		//print_matrix<int,50,7>(team_paths);

		int total_of_can_reach_all_vertices = 0;
		int total_of_can_be_reached_by_all = 0;

		for(int i = 0; i < n;i++)
			if(can_reach_all(i))
				total_of_can_reach_all_vertices++;

		for(int i = 0;i < n;i++)
			if(can_be_reached_by_all(i))
				total_of_can_be_reached_by_all++;

		vector<int> result;
		result.push_back(total_of_can_reach_all_vertices);
		result.push_back(total_of_can_be_reached_by_all);
		return result;
	}
};

using namespace std;

int _tmain(int argc, _TCHAR* argv[]){
	string s[] = {"010","000","110"};
	int i[] = { 1,  1 };

	TeamBuilder t;
	are_equal<int>(to_vector<int,2>(i),t.specialLocations(to_vector<string,3>(s)));

	string s1[] = {"0010","1000","1100","1000"};
    int i1[] = { 1,  3 };
	are_equal<int>(to_vector<int,2>(i1),t.specialLocations(to_vector<string,4>(s1)));

	string s2[] = {"01000","00100","00010","00001","10000"};
    int i2[] = { 5,  5 };
	are_equal<int>(to_vector<int,2>(i2),t.specialLocations(to_vector<string,5>(s2)));

	string s3[] = {"0110000","1000100","0000001","0010000","0110000","1000010","0001000"};
	int i3[] =  { 1,  3 };
	are_equal<int>(to_vector<int,2>(i3),t.specialLocations(to_vector<string,7>(s3)));

	int ii;
	cin >> ii;
	return 0;
}