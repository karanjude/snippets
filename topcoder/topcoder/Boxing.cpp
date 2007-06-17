/*

Problem Statement
    
People enjoy mazes, but they also get them dirty. Arrows, graffiti, and chewing gum are just a few of the souvenirs people leave on the walls. You, the maze keeper, are assigned to whiten the maze walls. Each face of the wall requires one liter of paint, but you are only required to paint visible faces. You are given a map of the maze, and you must determine the amount of paint needed for the job.
The maze is described by a vector <string> maze, where each character can be either '#' (a wall) or '.' (an empty space). All '.' characters on the perimeter of the map are considered entrances to the maze. Upon entering the maze, one can only move horizontally and vertically through empty spaces, and areas that are not reachable by these movements are not considered visible. Each '#' represents a square block with four wall faces (each side of the square is a face). A face is visible if it is not directly adjacent to another wall (and is in a reachable area of the maze). For example, two adjacent blocks can have at most six visible faces since two of their faces are directly adjacent to each other. All exterior faces on the perimeter are considered visible.
For example, the following picture represents a trivial maze with just one (wide) entrance and only four empty reachable spaces:  
 
To whiten this maze you must paint the faces highlighted in yellow above: 16 for its perimeter, plus 8 interior faces. Note that there are faces that are not visible and thus need not be painted.
Definition
    
Class:
TroytownKeeper
Method:
limeLiters
Parameters:
vector <string>
Returns:
int
Method signature:
int limeLiters(vector <string> maze)
(be sure your method is public)
    

Constraints
-
maze will contain between 1 and 50 elements, inclusive.
-
Each element of maze will contain between 1 and 50 characters, inclusive.
-
All elements of maze will have the same number of characters.
-
All characters in maze will be either '.' or '#'.
Examples
0)

    
{"##..#"
,"#.#.#"
,"#.#.#"
,"#####"}
Returns: 24
Example from the problem statement.
1)

    
{"##",
 "##"}
Returns: 8
Only the perimeter of the maze (which has no interior!) has to be painted.
2)

    
{"######"
,"#....."
,"#.####"
,"#.#..#"
,"#.##.#"
,"#....#"
,"######"}
Returns: 56

3)

    
{"######"
,"#....."
,"#..#.."
,"#....."
,"######"}
Returns: 36

4)

    
{"#.#.#.#"
,".#.#.#."
,"#.#.#.#"
,".#.#.#."}
Returns: 36

This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.
*/

#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <cctype>
#include <set>
#include <list>

#include <utility.cpp>

using namespace std;

class Boxing{

	set<int> populate_set(vector<int> a , vector<int> b , vector<int> c , vector<int> d , vector<int> e){
		set<int> result;
		for(int i = 0;i < a.size();i++)
			result.insert(a[i]);
		for(int i = 0;i < b.size();i++)
			result.insert(b[i]);
		for(int i = 0;i < c.size();i++)
			result.insert(c[i]);
		for(int i = 0;i < d.size();i++)
			result.insert(d[i]);
		for(int i = 0;i < e.size();i++)
			result.insert(e[i]);
		return result;
	}

	bool more_than_3_judges_fall_in(vector<int> a , vector<int> b , vector<int> c ,
		vector<int> d , vector<int> e , int lower , int upper){
		int count  = 0;
		bool f = false;
		for(int i = 0; i < a.size(); i++)
			if(a[i] >= lower && a[i] <= upper)
			{f = true ; break;}
		if(f) count++;
		f = false;
		for(int i = 0; i < b.size(); i++)
			if(b[i] >= lower && b[i] <= upper)
			{f = true ; break;}
		if(f) count++;
		f = false;
		for(int i = 0; i < c.size(); i++)
			if(c[i] >= lower && c[i] <= upper)
			{f = true ; break;}
		if(f) count++;
		f = false;
		for(int i = 0; i < d.size(); i++)
			if(d[i] >= lower && d[i] <= upper)
			{f = true ; break;}
		if(f) count++;
		f = false;
		for(int i = 0; i < e.size(); i++)
			if(e[i] >= lower && e[i] <= upper)
			{f = true ; break;}
		if(f) count++;
		f = false;
		if(count >= 3 ) return true;
		return false;
	}

	int at(set<int>  s , int index){
		int k ;
		set<int>::iterator ii;
		int val = 0;
		for(ii = s.begin(),k=0,val = *ii; k < index;ii++,k++)
			val = *ii;
		return val;
	}

	int at(set<int> s ,int index,set<int>::iterator ii){
		int k ;
		set<int>::iterator i;
		int val = 0;
		for(i = ii,k=0,val = *i; k < index && index < s.size();i++,k++)
			val = *i;
		return val;
	}

	int filter_all_where_lower_bound_of_1_matches_upper_bound_of_other(vector<pair<int,int>> l){
		map<pair<int,int>,vector<pair<int,int> > > m;
		list<pair<int,int>> result(l.begin(),l.end());

		for(int i = 0;i != l.size();i++){
				vector<pair<int,int>> v;
			for(int j = 0; j != l.size();j++){
				bool disjoint = true;
				if(i != j){
					int this_lower = l[i].first;
					int this_upper = l[i].second;
					int other_lower = l[j].first;
					int other_upper = l[j].second;
					int upper_as_ref = l[i].second;
					if(((other_lower > this_upper))){
						v.push_back(l[j]);
					}
				}
			}
				m.insert(make_pair(l[i],v));

		}

			return result.size();
	}
public:
	int maxCredit(vector<int> a,vector<int> b,vector<int> c,vector<int> d,vector<int> e){
		int count  = 0;
		vector<pair<int,int>> l;
		set<int> full_set = populate_set(a,b,c,d,e);
		int set_size = full_set.size();
		int max_val = at(full_set,set_size);;
		for(int i = 0 ; i < max_val; i++){
			for(set<int>::iterator j = full_set.begin() ; j != full_set.end() ; j++){
				if(set_size >= i){
					int lower_bound = *j;
					int upper_bound =  at(full_set,i,full_set.begin());;
					if ( upper_bound >= lower_bound && (upper_bound - lower_bound <= 1000) && more_than_3_judges_fall_in(a,b,c,d,e,lower_bound,upper_bound)){
						count++;
						l.push_back(make_pair(lower_bound,upper_bound));
						cout << endl << lower_bound << " - " << upper_bound;
					}
				}
			}
		}
		int result = filter_all_where_lower_bound_of_1_matches_upper_bound_of_other(l);
		return result;
	}
};

int _tmain(int argc, _TCHAR* argv[]){

	Boxing bb;

int a[] = {1,2,3,4,5,6};

int b[] = {1,2,3,4,5,6,7};

int c[] = {1,2,3,4,5,6};

int d[] = {0,1,2};

int e[] = {1,2,3,4,5,6,7,8};

	are_equal_with_print<int>(6,
		bb.maxCredit(to_vector<int,6>(a),
		to_vector<int,7>(b),
		to_vector<int,6>(c),
		to_vector<int,3>(d),
		to_vector<int,8>(e)));

	int a1[] = {5000,6500};

int b1[] = {6000};

int c1[] = {6500};

int d1[] = {6000};

int e1[]  = {0,5800,6000};

	are_equal_with_print<int>(1,
		bb.maxCredit(to_vector<int,2>(a1),
		to_vector<int,1>(b1),
		to_vector<int,1>(c1),
		to_vector<int,1>(d1),
		to_vector<int,3>(e1)));

	int ii;
	cin >> ii;
	return 0;
}