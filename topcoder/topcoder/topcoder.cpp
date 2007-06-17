// topcoder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

#include <utility.cpp>


using namespace std;

static int layer[400][600];

class grafixMask {

private :
	
	void block_layer_with(vector<string> rectangles){
		int x1 , y1 , x2 , y2;

		for( int i =  0; i < rectangles.size() ; i++) {
			istringstream iss(rectangles[i]);
			iss >> y1 >> x1 >> y2 >> x2;
	
			
			for(int y = y1; y <= y2; y++ ) {
				for(int x = x1; x <= x2 ; x++ ) {
					layer[y][x] = 1;
				}
			}
		}
	}

	int find_hole_area( int x , int y){
		stack<pair<int,int>> s ;
		
		s.push(make_pair(x,y));

		int result = 0;
		while(s.empty() == false){
			pair<int,int> p = s.top();
			s.pop();

			int xx = p.first;
			int yy = p.second;

			if(xx < 0 || xx >= 600 || yy < 0 || yy >= 400 || layer[yy][xx]) continue;

			layer[yy][xx] = 1;
			result++;
			s.push(make_pair(xx-1,yy));
			s.push(make_pair(xx+1,yy));
			s.push(make_pair(xx,yy-1));
			s.push(make_pair(xx,yy+1));

		}
			return result;
	}

	vector<int> find_holes_areas_in_layer(){
		vector<int> result;
		for(int y = 0 ; y < 400 ; y++) {
			for(int x = 0 ; x < 600 ; x++){
				if(!layer[y][x]){
					result.push_back(find_hole_area(x,y));
				}
			}
		}
		return result;
	}


public :
	vector<int> sortedAreas(vector<string> rectangles){
		block_layer_with(rectangles);
		vector<int> holes;
		holes = find_holes_areas_in_layer();
		sort(holes.begin(),holes.end());
		return holes;
	}
};






/*

int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	string rectangles[] = {"0 292 399 307"};
	int result[] = { 116800,  116800 };

	grafixMask g;
	//are_equal(to_vector<int,2>(result) , g.sortedAreas(to_vector<string , 1>(rectangles))  );
	 
	string rectangles1[] = {"48 192 351 207", "48 392 351 407", "120 52 135 547", "260 52 275 547"};
	int result1[] = { 22816,  192608 };

	are_equal(to_vector<int,2>(result1) , g.sortedAreas(to_vector<string , 4>(rectangles1))  );



	cin >> i;
}
*/
