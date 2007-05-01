/*
Problem Statement

You are the manager of a small taxi firm with 2 cars. On a particular evening, you have a number of customers who wish to travel between various locations, and you have to decide how to schedule the trips. Both of your cars start out at your base at location 0, and as manager, you have to wait for both of the cars to return to base before you can leave work for the night. Your goal is to minimize the amount of time before all of the customers have been delivered to their destinations and the cars have both returned to location 0.  The area in which your customers want to travel is represented by M locations, indexed from 0 to M-1, some of which are connected by roads.

You will be given a vector <string> roads, where the j-th digit of the i-th element is the time to travel on the direct road from location i to location j, or '0' if no direct route between these locations exists. You will also be given a vector <string> customers, where each element contains two space-separated integers that represent the indices of the starting location and destination of a customer. Customers have no preference as to which car picks them up and you may schedule the customers in any order, but once a car has picked up a customer, it must take him or her immediately to the required destination; the customer cannot be dropped off at an intermediate location to be picked up again later. Customers will also not share a car with each other, so if a taxi is carrying a customer it may not pick up another one. Picking up or dropping off a customer takes negligible time.  You should return the minimum amount of time before both of your cars have returned to base and you can go home for the night.
Definition

Class:
TaxiManager
Method:
schedule
Parameters:
vector <string>, vector <string>
Returns:
int
Method signature:
int schedule(vector <string> roads, vector <string> customers)
(be sure your method is public)


Notes
-
roads will not necessarily be symmetric. Therefore the time taken to drive from location i to j may not be the same as the time to drive from j to i.
Constraints
-
roads will contain between 2 and 50 elements, inclusive.
-
Each element of roads will contain exactly M characters, where M is the number of elements in roads.
-
Each character in roads will be a digit ('0' - '9').
-
The i-th character in the i-th element of roads will be '0'.
-
Each location will be reachable from all other locations.
-
customers will contain between 1 and 12 elements, inclusive.
-
Each element in customers will contain 2 distinct space-separated integers.
-
Each integer in customers will be between 0 and M-1, inclusive, with no leading zeros.
Examples

0)


{"020200"
,"202020"
,"020002"
,"200020"
,"020202"
,"002020"}
{"5 3","2 4","1 5","3 2"}
Returns: 16
An example of an optimal schedule is: Time    Action 0       Car 1 - Drive to location 3 0       Car 2 - Drive to location 1 2       Car 1 - Pick up customer 3, then drive to location 0, then 1, then 2 2       Car 2 - Pick up customer 2, then drive to location 2, then 5 6       Car 2 - Drop off customer 2, pick up customer 0, then drive to location 4, then 3 8       Car 1 - Drop off customer 3, pick up customer 1, then drive to location 1, then 4 10      Car 2 - Drop off customer 0, then drive to location 0 12      Car 2 - Arrive back at base 12      Car 1 - Drop off customer 1, then drive to location 1, then 0 16      Car 1 - Arrive back at base

1)


{"00020251090265906661"
,"00763002550100090081"
,"06003699000080062771"
,"00000710460400035310"
,"50000039119198350060"
,"66060004050810046028"
,"02333108565000200880"
,"40212560000209205231"
,"02601150098329905062"
,"00210383709951005203"
,"10111087340780827070"
,"05065800003095040140"
,"15604020082000100090"
,"83430030070580600750"
,"10588355007006001150"
,"14400080790005400536"
,"23400990400933060004"
,"11053016300602000090"
,"90040920084059282502"
,"61300007077904050900"}
{"0 19","4 16","15 16","4 18","2 7","9 15","11 6","7 13","19 13","12 19","14 12","16 1"}
Returns: 33

2)


{"095222800320504"
,"107600288090501"
,"760973530769345"
,"963093337510830"
,"338404069255826"
,"291700050155264"
,"002783031709004"
,"404730701707712"
,"068870030090995"
,"320025180036103"
,"468695042801904"
,"233626561000105"
,"070014432197086"
,"887301000143802"
,"230852749990330"}
{"3 6","0 4","2 7","9 7","13 9","1 6","7 13","14 2","8 7","10 1","11 13","7 12"}
Returns: 28

3)


{"00401","50990","00062","08008","03000"}
{"2 4"}
Returns: 14
With only one customer, you only need to send out one car.

Author : Karan Singh
this program requires a dynamic solution , the funda is that given the distance between all vertices and a set of vertices
we need to figure out the best of partioning the set of vertices into sets such that sum of the distance of vertices in each
corresponding set is minimized

we use dynamic programming for that , there is problem related twist , called state which we use to figure out
what which partioning scheme we have already used

*/
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <map>
#include <queue>
#include <list>

#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <set>

#include "utility.cpp"

using namespace std;
using namespace my;

int m[50][50];
int c[50][2];
int cache[50][1<<12];

class TaxiManager{
int cn;
public:
	int schedule(vector <string> roads, vector <string> customers){
		memset(m,0,sizeof(m));
		memset(c,0,sizeof(c));
		memset(cache,-1,sizeof(cache));
		int n = roads.size();
		for(int i = 0; i != n; i++){
			for(int j = 0;j != n;j++){
				int r = roads[i][j]-'0';
				if(r == 0)
					r = INT_MAX/2;
				m[i][j] = r;
			}
		}

		for(int k = 0;k  < n;k++){
			for(int i = 0;i< n;i++){
				for(int j = 0;j < n;j++){
					m[i][j] = min(m[i][j],m[i][k] + m[k][j]);
				}
			}
		}

		cn = customers.size();
		for(int i =0;i < cn;i++){
			istringstream iss(customers[i]);
			int f,t;
			iss >> f >> t;
			c[i][0] = f;
			c[i][1] = t;
		}
		int r = INT_MAX;
		for(int i = 0;i < (1<<cn);i++){
			int c1 = i;
			int c2 = ((1<<cn)-1) ^ i;
			r = min(r,max(go(0,c1),go(0,c2)));
		}
		return r;
	}

	int go(int loc,int state){
		if(state == 0)
			return m[loc][0];
		if(cache[loc][state] != -1)
			return cache[loc][state];
		int r = INT_MAX/2;
		for(int i = 0;i < cn;i++){
			if(state & (1 << i)){
				int d = m[loc][c[i][0]];
				int x = m[c[i][0]][c[i][1]];
				r = min(r,d+x+go(c[i][1],(1<<i)^state));
			}
		}

		return cache[loc][state] = r;
	}
};

int main(){

string s[] = 	{"020200"
,"202020"
,"020002"
,"200020"
,"020202"
,"002020"};

string c[]= {"5 3","2 4","1 5","3 2"};
	TaxiManager t;
	cout << t.schedule(to_vector<string,6>(s),to_vector<string,4>(c));
	int number;
	cin >> number;
	return 0;
}