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

int island_to_island_map[50][50][50];
int island_to_ferry_map[50][50];

struct Island{
	Island(int number,int cost){
		this->cost = cost;
		this->number = number;
		remaining_tickets.clear();
	}
	vector<pair<int,int>> remaining_tickets;
	int number;
	int cost;
};

bool operator < (const Island &left , const Island &right){
	return left.cost > right.cost;
}

class IslandFerries{
private:
	int number_of_islands ;
	int number_of_ferry_services;

	void initialize_maps(){
		memset(island_to_island_map,0,sizeof(island_to_island_map));
		memset(island_to_ferry_map,0,sizeof(island_to_ferry_map));
	}

	void populate_maps(vector<string> legs,vector<string> prices){
		number_of_islands = prices.size();
		number_of_ferry_services = legs.size();
		populate_island_to_island_map(legs);
		populate_island_to_ferry_map(prices);
	}

	void populate_island_to_ferry_map(vector<string> prices){
		for(int i = 0; i < prices.size(); i++){
			istringstream iss(prices[i]);
			int ferry_number = 0;
			int ferry_ticket_cost = 0;
			while(iss >> ferry_ticket_cost){
				island_to_ferry_map[ferry_number][i] = ferry_ticket_cost;
				ferry_number++;
			}
		}
	}


	void populate_island_to_island_map(vector<string> legs){
			for(int i = 0;i < legs.size(); i++){
			istringstream iss(legs[i]);
			string leg;
			while(iss >> leg ){
				vector<string> link = split_string(leg,"-");
				int from = atoi(link[0].c_str());
				int  to = atoi(link[1].c_str());
				island_to_island_map[i][from][to] = 1;
			}
		}
	}

	bool mod_lesser(pair<int,int> left , pair<int,int> right){
		return left.first < right.first;
	};
public:
	vector<int> costs(vector<string> legs,vector<string> prices){
		initialize_maps();
		populate_maps(legs,prices);
		vector<int> v(number_of_islands-1,-1);
		vector<int> visited(number_of_islands,0);
		Island island(0,0);
		priority_queue<Island> q;
		q.push(island);
		int from = 0;
		while(!q.empty()){
			island = q.top();
			if(visited[island.number]){
				q.pop();continue;
			}
			if(island.number != 0 && v[island.number-1] == -1 ){
				v[island.number-1] = island.cost;
				visited[island.number] = 1;
			}
			from = island.number;
			for(int to = 0; to < number_of_islands;to++){
					for(int ferry_type = 0;ferry_type < number_of_ferry_services;ferry_type++){
						if(island.number != to && island_to_island_map[ferry_type][island.number][to]){
							if(island_to_ferry_map[ferry_type][from]){
								int cost = island_to_ferry_map[ferry_type][from];
								vector<pair<int,int>> remaining_tickets ;
								for(int i = 0; i < number_of_ferry_services ; i++){
									if(i != ferry_type){
										int value = island_to_ferry_map[i][from];
										remaining_tickets.push_back(make_pair(value,i));
									}
								}


								int cost_to_destination  = island.cost + cost;
								if(island.remaining_tickets.size() > 0){
									vector<pair<int,int>> ::iterator ticket = min_element(island.remaining_tickets.begin(),island.remaining_tickets.end());
								
									if(island_to_ferry_map[(*ticket).second][from]){
											int min_value = (*ticket).first;
											if(min_value <  cost_to_destination){
												cost_to_destination = min_value + island.cost;
												remaining_tickets.push_back(make_pair(cost,ferry_type));
											}
										}
									}
								Island destination = Island(to,cost_to_destination);
								destination.remaining_tickets = remaining_tickets;
								q.push(destination);
							}
					}
				}
			}
				
			q.pop();
		}
		return v;
	}
};

/*int _tmain(int argc, _TCHAR* argv[]){
 string f[] = { "0-1 0-3", "0-2" };
 string i[] = { "5 7", "1000 1000", "1000 1000", "1000 1000" };
 int e[] = { 5,  7,  5 };

 IslandFerries ii;
 vector<int> r = ii.costs(to_vector<string,2>(f),to_vector<string,4>(i));
 are_equal<int>(to_vector<int,3>(e),r);

string f1[] = { "1-0" };
 string i1[] = { "793", "350" };
 int e1[] = { -1 };

  vector<int> r1 = ii.costs(to_vector<string,1>(f1),to_vector<string,2>(i1));
 are_equal<int>(to_vector<int,1>(e1),r1);

string f2[] = { "0-1 1-2 2-3", "0-1 2-3" };
string i2[] = { "1 10", "20 25", "50 50", "1000 1000", "1000 1000" };
int e2[] = { 1,  11,  31,  -1 };

  vector<int> r2 = ii.costs(to_vector<string,2>(f2),to_vector<string,5>(i2));
 are_equal<int>(to_vector<int,4>(e2),r2);

string f4[]={"8-18 4-11 15-5 7-12 11-8 0-15 15-2 3-11 4-18 2-3",
 "16-2 18-3 15-18 11-19 18-2 18-7 19-17 3-15 12-19",
 "2-17 0-12 1-2 14-12 6-2 4-2 11-5 4-11 11-6 17-16",
 "0-18 13-18 16-0 3-7 14-12 3-1 19-18 3-19 10-3 8-15",
 "18-19 3-16 13-6 0-19 12-14 5-17 1-12 7-13 9-14 1-2",
 "14-5 17-9 2-10 16-13 11-15 10-17 14-10 0-14 2-13",
 "4-5 0-17 6-9 17-7 12-6 5-6 6-18 10-18 0-2 13-0 8-4",
 "3-12 4-11 10-17 13-12 3-0 3-7 13-0 9-15 10-9 0-10" };

string i4[]={"592 219 88 529 324 86 503 610",
 "2 94 8 600 34 95 6 494",
 "638 301 10 246 290 97 85 74",
 "118 8 939 393 450 79 317 99",
 "99 806 698 740 2 26 525 818",
 "95 9 615 972 23 23 5 666",
 "6 448 440 710 83 4 419 496",
 "4 47 182 4 185 70 718 770",
 "3 321 6 855 968 65 10 6",
 "173 224 300 3 79 2 707 49",
 "21 10 7 10 4 9 5 8",
 "6 600 4 724 7 1 960 247",
 "83 16 901 50 437 780 658 2",
 "763 923 125 576 45 423 3 1",
 "7 324 391 898 8 59 281 973",
 "9 44 49 364 78 744 43 5",
 "10 62 75 418 216 90 32 919",
 "764 534 778 605 80 647 821 74",
 "65 449 102 867 421 94 6 7",
 "67 155 362 789 189 316 107 595" };


int e4[]={ 170,  160,  155,  173,  145,  150,  158,  168,  153,  145,  162,  88,  162,  86,  163,  159,  153,  150,  104 };

  vector<int> r4 = ii.costs(to_vector<string,8>(f4),to_vector<string,20>(i4));
 are_equal<int>(to_vector<int,19>(e4),r4);


 string f3[] = { "0-1", "1-0", "0-2", "2-3"} ;
 string i3[] = { "1 1 1000 1000", "1000 1000 10 100", "1000 1000 1000 1000", "1000 1000 1000 1000" };
 int e3[] =  { 1,  12,  112 };

  vector<int> r3 = ii.costs(to_vector<string,4>(f3),to_vector<string,4>(i3));
 are_equal<int>(to_vector<int,3>(e3),r3);

 int ans;
 cin >> ans;
 return 0;
}*/