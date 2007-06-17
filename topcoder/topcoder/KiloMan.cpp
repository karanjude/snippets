#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <algorithm>

#include <utility.cpp>


using namespace std;

struct node{
	node(int weapons,int shots_taken){
		this->weapons = weapons;
		this->shots_taken = shots_taken;
	}

	int shots_taken;
	int weapons;

};



bool operator < (const node &leftNode , const node &rightNode){
	if(leftNode.shots_taken != rightNode.shots_taken) return leftNode.shots_taken > rightNode.shots_taken;
	if(leftNode.weapons != rightNode.weapons) return leftNode.weapons > rightNode.weapons;
		return false;
}

static int visited[1 << 15];

class KiloManX{
	void initialize(){
		memset(visited,0,1<<15);
	}
public:
	int leastShots(vector<string> damageChart , vector<int> bossHealth){
		initialize();
		priority_queue<node> q;
		q.push(node(0,0));
		int total_enemies = damageChart.size();
		while(!q.empty()){
			node top = q.top();
			q.pop();

			if(visited[top.weapons]) continue;
				visited[top.weapons] = 1;

			if(top.weapons == (1 << total_enemies) - 1)
				return top.shots_taken;
			
			for(int i = 0 ; i < damageChart.size() ; i++){
				if((top.weapons >> i) & 1) continue;

				int boss_health = bossHealth[i];
				int min_shots = boss_health;
				
				for(int j = 0; j < damageChart.size(); j++){
					if(i == j) continue;
				
					int damage_weapon_can_do = damageChart[j][i] - '0';
					if(((top.weapons >> j) & 1) &&  damage_weapon_can_do){
						int shots_needed = boss_health / damage_weapon_can_do;
						if((boss_health % damage_weapon_can_do) != 0 ) 
							shots_needed++;
						min_shots = min(min_shots,shots_needed);
					}
				}
				q.push(node(top.weapons | (1 << i), top.shots_taken + min_shots));
			}
		}
	}
};

/*

int _tmain(int argc, _TCHAR* argv[]){
	KiloManX k;

	string s[] = {"070","500","140"};
	int i[] = {150,150,150};

	are_equal_with_print<int>(218,k.leastShots(to_vector<string,3>(s),to_vector<int,3>(i)));

	string s1[] =  {"1542", "7935", "1139", "8882"};

	int i1[] = {150,150,150,150};

	are_equal_with_print<int>(205,k.leastShots(to_vector<string,4>(s1),to_vector<int,4>(i1)));

	string s2[] =  {"07", "40"};

	int i2[] = {150,10};

	are_equal_with_print<int>(48,k.leastShots(to_vector<string,2>(s2),to_vector<int,2>(i2)));

	string s3[] = {"02111111", "10711111", "11071111", "11104111",
 "41110111", "11111031", "11111107", "11111210"};

 int i3[] = {28,28,28,28,28,28,28,28};

	are_equal_with_print<int>(92,k.leastShots(to_vector<string,8>(s3),to_vector<int,8>(i3)));


	string s4[] = {"198573618294842",
 "159819849819205",
 "698849290010992",
 "000000000000000",
 "139581938009384",
 "158919111891911",
 "182731827381787",
 "135788359198718",
 "187587819218927",
 "185783759199192",
 "857819038188122",
 "897387187472737",
 "159938981818247",
 "128974182773177",
 "135885818282838"};

int i4[] = {157, 1984, 577, 3001, 2003, 2984, 5988, 190003,
9000, 102930, 5938, 1000000, 1000000, 5892, 38};

	are_equal_with_print<int>(260445,k.leastShots(to_vector<string,15>(s4),to_vector<int,15>(i4)));

    int ii;
	cin >> ii;
	return 0;
}
*/