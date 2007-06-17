#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <cctype>
#include <string>

#include <utility.cpp>

using namespace std;

class GroceryBagger{
	map<string,int> _table; 
public:
	int minimumBags(int strength,vector<string> itemType){
		_table.clear();
		if(itemType.size() == 0)
			return 0;
		for(int i = 0;i != itemType.size(); i++)
			if(_table.find(itemType[i]) == _table.end())
				_table[itemType[i]] = 1;
			else
				_table[itemType[i]]++;

		int bags_needed = 0;
		for(map<string,int>::iterator ii =  _table.begin(); ii != _table.end(); ii++){
			int qty = ii->second;
			int q = qty / strength;
			if(qty % strength)
				q++;
			bags_needed += q;
		}
		return bags_needed;
	}
};

int _tmain(int argc, _TCHAR* argv[]){

string s[] = {"DAIRY",
 "DAIRY",
 "PRODUCE",
 "PRODUCE",
 "PRODUCE",
 "MEAT"};

GroceryBagger g;
are_equal_with_print<int>(4,g.minimumBags(2,to_vector<string,6>(s)));

string s1[] = {"DAIRY",
 "DAIRY",
 "PRODUCE",
 "PRODUCE",
 "PRODUCE",
 "MEAT"};

 are_equal_with_print<int>(3,g.minimumBags(3,to_vector<string,6>(s1)));

string s2[] = {""};

are_equal_with_print<int>(0,g.minimumBags(10,to_vector<string,0>(s2)));

string s3[] = {"CANNED",   "CANNED",  "PRODUCE",
 "DAIRY",    "MEAT",    "BREAD",
 "HOUSEHOLD","PRODUCE", "FROZEN",
 "PRODUCE", "DAIRY"};

are_equal_with_print<int>(7,g.minimumBags(5,to_vector<string,11>(s3)));

string s4[] = {"CANNED",   "CANNED",  "PRODUCE",
 "DAIRY",    "MEAT",    "BREAD",
 "HOUSEHOLD","PRODUCE", "FROZEN",
 "PRODUCE", "DAIRY"};

are_equal_with_print<int>(8,g.minimumBags(2,to_vector<string,11>(s4)));

	int ii;
	cin >> ii;
	return 0;
}