#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <stack>

using namespace std;

static int layer[400][600];

class grafixMask {

private :
	
	void block_layer_with(vector<string> rectangles){
		int x1 , y1 , x2 , y2;

		for( int i =  0; i <= rectangles.size() ; i++) {
			istringstream iss(rectangles[i]);
			iss >> y1 >> x1 >> y2 >> x2;
		}
		
		for(int y = y1; y <= y2; y++ ) {
			for(int x = x1; x <= x2 ; x++ ) {
				layer[y][x] = 1;
			}
		}
	}

	int find_hole_area( int x , int y){
		int dx[] = { -1 , 1 , 0  , 0};
		int dy[] = {  0 , 0 , -1 , 1} ;
		
		stack<pair<int,int>> s ;
		
		s.push(make_pair(x,y));

		int result = 0;
		while(s.empty() == false){
			pair<int,int> p = s.top();
			s.pop();

			int xx = p.first;
			int yy = p.second;

			if(xx < 0 || xx > 600 || yy < 0 || yy > 400 || layer[yy][xx]) continue;

			layer[yy][xx]++;

			for(int k = 0; k < 4; k ++){
				int _x = xx + dx[k];
				int _y = yy + dy[k];
				s.push(make_pair(_x,_y));
			}
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
		return holes;
	}
};



template<class T , int SIZE>
vector<T> to_vector(T source[]){
	vector<T> result;
	for(int i = 0 ; i < SIZE ; i++)	{
		result.push_back(source[i]);
	}
	return result;
}

template<class T>
bool are_equal(vector<T> v1 , vector<T> v2){
	bool result = true;
	result = v1.size() == v2.size();
	for(int i = 0; i < v1.size(); i++){
		if(v1[i] != v2[i]) {
			result = false;
			break;
		}
	}

	return result;
}

template<class T>
void print(vector<T> v){
	cout << endl;
	for(int i = 0; i < v.size() ; i++) {
		cout << "  " << v[i];
	}
}

void main(){
	int i = 0;

	 string s[] = {"0 292 399 307"};

	 vector<string> expected ;
     expected = to_vector<string , 1 >(s);
	 grafixMask g;
	 cin >> i;
	vector<int> r = g.sortedAreas(expected);
	 

	cin >> i;
}