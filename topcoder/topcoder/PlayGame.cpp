#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <cctype>
#include <string>
#include <list>
#include <utility.cpp>

using namespace std;

class PlayGame{
	int find_you_bigger_than(vector<int> you,vector<int> used,int val){
		int index = -1;
		for(int i = 0;i < you.size(); i++){
			if(you[i] > val && !used[i]){
				index = i;
				break;
			}
		}
		return index;
	}
public:
	int saveCreatures(vector<int> you, vector<int> computer){
		sort(you.begin(),you.end());
		sort(computer.begin(),computer.end());
		vector<int> used(you.size(),0);
		int sum = 0;
		int j = -1;
		for(int i = computer.size()-1;i > 0; i--){
			if(( j = find_you_bigger_than(you,used,computer[i])) != -1){
				sum += you[j];
				used[j] = 1;
			}
		}
		return sum;
	}

	 /*int saveCreatures(vector <int> a, vector <int> b) {
    sort(a.begin(),a.end());
	sort(b.begin(),b.end());
    int s = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
      //if larger
      for (int j = b.size() - 1; j >= 0; j--) {
        if (a[i] > b[j]) {
          s += a[i];
          b.erase(b.begin() + j);
          goto hit;
        }
      }
      b.erase(b.end() - 1);
      hit:;
    }
    return s;
  }*/

};

int _tmain(int argc, _TCHAR* argv[]){

	int u[] = {5, 15, 100, 1, 5};
	int c[] = {5, 15, 100, 1, 5};
	PlayGame p;
	are_equal_with_print<int>(120,p.saveCreatures(to_vector<int,5>(u),to_vector<int,5>(c)));

	int u1[] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 
 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
	int c1[] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 
 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
	are_equal_with_print<int>(0,p.saveCreatures(to_vector<int,50>(u1),to_vector<int,50>(c1)));


	int u2[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int c2[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	are_equal_with_print<int>(99,p.saveCreatures(to_vector<int,10>(u2),to_vector<int,10>(c2)));

	int u3[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	int c3[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	are_equal_with_print<int>(65,p.saveCreatures(to_vector<int,10>(u3),to_vector<int,10>(c3)));

	int u4[] = {651, 321, 106, 503, 227, 290, 915, 549, 660, 115,
 491, 378, 495, 789, 507, 381, 685, 530, 603, 394,
 7, 704, 101, 620, 859, 490, 744, 495, 379, 781,
 550, 356, 950, 628, 177, 373, 132, 740, 946, 609,
 29, 329, 57, 636, 132, 843, 860, 594, 718, 849};

	int c4[] = {16, 127, 704, 614, 218, 67, 169, 621, 340, 319,
 366, 658, 798, 803, 524, 608, 794, 896, 145, 627,
 401, 253, 137, 851, 67, 426, 571, 302, 546, 225,
 311, 111, 804, 135, 284, 784, 890, 786, 740, 612,
 360, 852, 228, 859, 229, 249, 540, 979, 55, 82};
	are_equal_with_print<int>(25084,p.saveCreatures(to_vector<int,50>(u4),to_vector<int,50>(c4)));

	int ii;
	cin >> ii;
	return 0;
}