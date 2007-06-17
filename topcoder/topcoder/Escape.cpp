#include "stdafx.h"
#include <utility.cpp>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <set>

using namespace std;

#define MAX (500)

static int _grid[MAX][MAX];

map< pair<int,int> , int> cache;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,-1,0,1};

class Escape{
private :
	void initialize(){
		memset(_grid,0,MAX+1 * MAX+1);
		cache.clear();
	}

	void setAreas(vector<string> values,int value){
		for(int i = 0; i < values.size();i++){
			istringstream ss(values[i]);
			int x1 , x2 , y1 , y2;
			ss >> x1 >> y1 >> x2 >> y2;
			setRange(x1,y1,x2,y2,value);
		}
	}

	void setRange(int x1,int y1,int x2,int y2,int value){
		if(y1 > y2) swap(y1,y2);
		if(x1 > x2) swap(x1,x2);
		for(int y = y1; y < y2;y++){
			for(int x = x1; x < x2;x++){
				_grid[y][x] = value;
			}
		}
	}

	int search(int x , int y){
		queue<pair<int,int>> q;
		q.push(make_pair(x,y));
		int lifeLost = 0;
		while(!q.empty()){
			pair<int,int> node = q.front();
			q.pop();
			cache[node] = lifeLost;
			for(int i = 0;i < 4;i++){
				int xx = node.first + dx[i];
				int yy = node.second + dy[i];
				if( xx < 0 || xx > MAX || yy < 0 || yy > MAX ) continue;
				pair<int,int> newNode = make_pair(xx,yy);
				int minLifeLost = cache[node] + _grid[node.first][node.second];
				if(!cache.count(newNode)){
					q.push(newNode);
					cache[newNode] = minLifeLost;
				}
			}
		}
		if(cache.count(make_pair(MAX,MAX)))
			return cache[make_pair(MAX,MAX)];
		return -1;
	}

	int bfs(int srcx, int srcy)
{
  set <pair<int,int>> totry;
  cache.clear();
  pair<int,int> src = make_pair(srcx,srcy);
  cache[src] = 0;
  totry.insert(src);
 
  int x = 0;
  while (totry.size())
  {
    srcx = totry.begin()->first;
    srcy = totry.begin()->second;
    src = make_pair(srcx, srcy);
/*    cout 
    x++;*/
 
    for (int dstx = srcx-1; dstx <= srcx+1; dstx++)
    for (int dsty = srcy-1; dsty <= srcy+1; dsty++)
    if (dstx >= 0 && dsty >= 0 && dstx <= 500 && dsty <= 500)
    if ( (dstx-srcx)*(dstx-srcx) + (dsty-srcy)*(dsty-srcy) == 1)
    {
      pair<int,int> dest = make_pair(dstx, dsty);
      int length = _grid[dsty][dstx];
      if (length < 2)
      if (!cache.count(dest) || cache[dest] > cache[src] + length)
      {
        cache[dest] = cache[src] + length;
        totry.insert(dest);
      }
    }
    totry.erase(src);
  }
  if(cache.count(make_pair(MAX,MAX)))
			return cache[make_pair(MAX,MAX)];
		return -1;
	}

public :
	int lowest(vector<string> harmful , vector<string> deadly){
		initialize();
		setAreas(harmful,1);
		setAreas(deadly,2);
		print_matrix<int,MAX,10>(_grid);
		return search(0,0);
	}

};


/*int _tmain(int argc, _TCHAR* argv[])
{
	string harmful_0[] = {"0 0 250 250","250 250 500 500"};
	string deadly_0[] = {"0 251 249 500","251 0 500 249"};

	Escape e;
	are_equal_with_print<int>(1000,e.lowest(to_vector<string,1>(harmful_0),to_vector<string,1>(deadly_0)));
	
	int i;
	cin >> i;
}
*/