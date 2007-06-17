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



int _dx[6] = {0, 0,1, 1,-1,-1};
int _dy[6] = {1,-1,1,-1, 1,-1};


class RoboCourier {
private:
	string p;
	int node_count;
	int destination;
	map<pair<int,int>,int> nodes;
	map<pair<int,int>,int> connectivity;

	
	void initialize(){
		p = "";
		node_count = 0;
		nodes.clear();
		connectivity.clear();
		destination = 0;
	}

	void make_complete_path(vector<string> path){
		for(int i = 0;i < path.size(); i++)
			p += path[i];
	}

	int get_or_add_node(int x,int y){
		int result;
		map<pair<int,int>,int> ::iterator ii;
		ii = nodes.find(make_pair(x,y));
		if(ii == nodes.end()){
			nodes.insert(make_pair(make_pair(x,y),++node_count));
			result = node_count;
		}
		else
			result = ii->second;
		return result;
	}

	void connect(int src,int dest,int dir){
		connectivity.insert(make_pair(make_pair(src,dir),dest));
		connectivity.insert(make_pair(make_pair(dest,(dir+3)%6),src));
	}

	void build_graph(){
		int x , y;
		x = y = 0 ;
		int dir = 0;
		for(int i = 0; i < p.length(); i++){
			switch(p[i]){
				case 'L' : dir = (dir + 5) % 6;
					break;
				case 'R' : dir = (dir + 1) %  6;
					break;
				case 'F' : 
					int src = get_or_add_node(x,y);
					x += _dx[dir];
					y += _dy[dir];
					int dest = get_or_add_node(x,y);
					connect(src,dest,dir);
					break;
			}
		}
		destination = get_or_add_node(x,y);
	}


public:
	
	int timeToDeliver(vector<string> path){
		initialize();
		make_complete_path(path);
		build_graph();
		return 0;
	}
};

/*
int _tmain(int argc, _TCHAR* argv[]){
	string s[] = 	{ "FRRFLLFLLFRRFLF" };
 
	RoboCourier r;
    are_equal_with_print<int>(15,r.timeToDeliver(to_vector<string,1>(s)));
	return 0;
}
*/