#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>

#include <utility.cpp>

using namespace std;

static int rgb_houses[20][3];

#define RED	  (0)
#define BLUE  (2)
#define GREEN (1)




struct Node {
	Node(int number , int color,int cost){
		this->number = number;
		this->color = color;
		this->cost = cost;
	}
	int number;
	int color;
	int cost;
};

bool operator < (const Node &left , const Node &right){
	return left.cost > right.cost;
}



class RGBStreet {
private:
	void initialize(void){
		memset(rgb_houses,0,sizeof(rgb_houses));
	}
	void populate_houses(vector<string> houses){
		for(int i = 0; i < houses.size(); i++){
			istringstream iss(houses[i]);;
			int j = 0;
			int value;
			while(iss >> value){
				rgb_houses[i][j++] = value;
			}
		}
	}

public: 
	int estimateCost(vector <string> houses){
		initialize();
		int n = houses.size();
		populate_houses(houses);
		int min_sum = 1000000;
		for(int i = 0 ;i < 3;i++){
			Node current_house = Node(0,i,rgb_houses[0][i]);
			priority_queue<Node> q;
			q.push(current_house);	
			while(!q.empty()){
				Node current_house = q.top();	q.pop();
				if(current_house.number == n-1){
					min_sum = min(min_sum,current_house.cost);
					break;
				}
				for(int i = 0;i < 3;i++){
					if(current_house.color != i){ 
						q.push(Node(current_house.number + 1,i,current_house.cost + rgb_houses[current_house.number+1][i]));		
					}
				}
			}
		}
		return min_sum;
	}
};


int _tmain(int argc, _TCHAR* argv[]){
	
	string s[] = {"1 100 100", "100 1 100", "100 100 1"};

	RGBStreet r;
	are_equal_with_print<int>(3,r.estimateCost(to_vector<string,3>(s)));

	string s1[] = {"1 100 100", "100 100 100", "1 100 100"};
	are_equal_with_print<int>(102,r.estimateCost(to_vector<string,3>(s1)));

	string s2[] = {"26 40 83", "49 60 57", "13 89 99"};
	are_equal_with_print<int>(96,r.estimateCost(to_vector<string,3>(s2)));

	string s3[] = {"26 40 83", "49 60 57", "13 89 99"};
	are_equal_with_print<int>(96,r.estimateCost(to_vector<string,3>(s3)));

    string s4[] = {"30 19 5", "64 77 64", "15 19 97", "4 71 57", "90 86 84", "93 32 91"};
	are_equal_with_print<int>(208,r.estimateCost(to_vector<string,6>(s4)));

	string s5[] = 	{"71 39 44", "32 83 55", "51 37 63", "89 29 100", 
	 "83 58 11", "65 13 15", "47 25 29", "60 66 19"};
	are_equal_with_print<int>(253,r.estimateCost(to_vector<string,8>(s5)));

	int ii;
	cin >> ii;
	return 0;
}