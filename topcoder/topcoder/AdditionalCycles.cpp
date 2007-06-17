#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <map>
#include <queue>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <set>
#include <new>
#include <cctype>

#include "utility.cpp"

using namespace std;
using namespace my;

struct winner{
	string name;
	int rating;
	double score;

	winner(string name,int rating , double score){
		this->name = name;
		this->rating = rating;
		this->score = score;
	}
};

bool operator < (const winner & left , const winner & right){
	if(left.rating != right.rating)
		return left.rating < right.rating;
	if(left.score != right.score)
		return left.score > right.score;
	return left.name < right.name;
}

class ContestScore { 
double _data[50][50];
vector<string> names;
int judges;
double _rating[50][50];
public:
	void build_data(int n,const vector<string> & data){
		for(int i = 0;i < n;i++){
			istringstream iss(data[i]);
			string s;
			iss >> s;
			names.push_back(s);
			double v;
			int j = 0;
			while(iss >> v){
				_data[i][j] = v;
				j++;
			}
			judges = j;
		}
	}
	
	void build_rating(int n){
			map<double,int> rating;
			vector<double> ratings;
	
		for(int cols = 0;cols < judges;cols++){
			for(int rows = 0;rows < n;rows++){
				ratings.push_back(_data[rows][cols]);
			}
			sort(ratings.begin(),ratings.end(),greater<double>());
			int cr =1;
			for(int rows = 0;rows < ratings.size();rows++){
				pair<double,int> r = make_pair(ratings[rows],cr);
				if(rating.find(ratings[rows]) == rating.end()){
					rating.insert(r);
				}
				cr++;
			}
			for(int rows = 0;rows < n;rows++){
				_rating[rows][cols] = rating[_data[rows][cols]];
			}
			ratings.clear();
			rating.clear();
		}

	}

	vector <string> sortResults(vector <string> data){
		memset(_data,0.0,sizeof(_data));
		names.clear();
		memset(_rating,0,sizeof(_rating));
		int n = data.size();
		build_data(n,data);
		build_rating(n);
		vector<winner> winners;
		for(int i = 0;i < n;i++){
			int r = 0;
			double s = 0;
			for(int j = 0;j < judges;j++){
				r += _rating[i][j];
				s += _data[i][j];
			}
			winners.push_back(winner(names[i],r,s));
		}
		sort(winners.begin(),winners.end());
		vector<string> result;
		for(int i = 0;i < winners.size();i++){
			ostringstream o;
			o << winners[i].name << " " << winners[i].rating << " " ;
			o.setf(ios::fixed);
			o.precision(1);
			o<< winners[i].score;
			result.push_back(o.str());
		}
		return result;
	}
};
int main(){

	ContestScore c;
	string d[] = {"A 90.7 92.9 87.4",
 "B 90.5 96.6 88.0",
 "C 92.2 91.0 95.3"};
	string r[] = { "C 5 278.5",  "B 6 275.1",  "A 7 271.0" };
	are_equal<string>(to_vector<string,3>(r),c.sortResults(to_vector<string,3>(d)));

	string d1[] = {"STANFORD 85.3 90.1 82.6 84.6 96.6 94.5 87.3 90.3",
 "MIT 95.5 83.9 80.4 85.5 98.7 98.3 96.7 82.7",
 "PRINCETON 99.2 79.1 87.6 85.1 93.6 96.4 86.0 90.6",
 "HARVARD 83.6 92.0 85.5 94.3 97.5 91.5 92.5 83.0",
 "YALE 99.5 92.6 86.2 82.0 96.4 92.6 84.5 78.6",
 "COLUMBIA 97.2 87.6 81.7 93.7 88.0 86.3 95.9 89.6",
 "BROWN 92.2 95.8 92.1 81.5 89.5 87.0 95.5 86.4",
 "PENN 96.3 80.7 81.2 91.6 85.8 92.2 83.9 87.8",
 "CORNELL 88.0 83.7 85.0 83.8 99.8 92.1 91.0 88.9"};
string r1[] = 
{ "PRINCETON 34 717.6",
  "MIT 36 721.7",
  "HARVARD 38 719.9",
  "COLUMBIA 39 720.0",
  "STANFORD 39 711.3",
  "YALE 40 712.4",
  "BROWN 41 720.0",
  "CORNELL 42 712.3",
  "PENN 51 699.5" };

	are_equal<string>(to_vector<string,9>(r1),c.sortResults(to_vector<string,9>(d1)));
 
	int number;
	cin >> number;
	return 0;
}