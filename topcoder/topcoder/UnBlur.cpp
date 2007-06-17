#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>
#include <list>
#include <string>
#include <cctype>
#include <string>
#include <utility.cpp>
#include <cmath> 

using namespace std;

template <class T>
ostream& operator <<(ostream& os, const vector<T>& a) {
  for(int i=0;i<(int)a.size();i++) {
    os << a[i] << endl;
  }
  os << endl;
  return os;
}


class Unblur{
	    
		void update(vector<string>  &b,vector<string> &r, int x,int y){
			r[y][x] = '#';

		for(int i = y-1; i <= y+1;i++){
				for(int j = x-1; j <= x+1; j++){
					if(i >= 0 && i < b.size() && j >= 0 && j < b[0].size()){
						b[i][j] -= 1;
					}
				}
			}
		}

public:
	vector<string> original(vector<string>  b){
		vector<string> r(b.size(),string(b[0].size(),'.'));
		for(int y = 1; y < b.size()-1; y++){
			for(int x = 1; x < b[0].size()-1;x++){
				if(b[y-1][x-1] == '1'){
					update(b,r,x,y);
				}
			}
		}
    cout << r;
    return r;    
  }

};

int _tmain(int argc, _TCHAR* argv[]){

	Unblur u;
	string s[] = {"1221", "1221", "1221"};
	string r[] = {"....", ".##.", "...."};
	are_equal(to_vector<string,3>(r),u.original(to_vector<string,3>(s)));

	string s1[] = {"1233321000000000123332100000000000000000000",
  "1244422233222332334343323322232112332223321",
  "1255523344343443545343434434343233432334432",
  "0033303455465775633011445546454355753457753",
  "0033303333364543533011433336333364521346542",
  "0033303455464532445343545546454355753446542",
  "0022202344342200234343434434343233432323221",
  "0011101233221100123332223322232112332211111" };


	string r1[] ={ "...........................................",
  ".#####...........#####.....................",
  "...#...####.####.#...#.####.###..####.####.",
  "...#...#..#.#..#.#.....#..#.#..#.#....#..#.",
  "...#...#..#.####.#.....#..#.#..#.###..####.",
  "...#...#..#.#....#...#.#..#.#..#.#....#.#..",
  "...#...####.#....#####.####.###..####.#..#.",
  "..........................................." }; 


	are_equal(to_vector<string,8>(r1),u.original(to_vector<string,8>(s1)));

	int ii;
	cin >> ii;
	return 0;
}