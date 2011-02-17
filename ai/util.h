#ifndef UTIL_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

extern vector< vector<int> > maze;
extern int x,y, width, height, sx, sy, ex, ey;
extern map< pair<int, int>, bool > visited;

inline int abs(int x){
  if( x < 0)
    return -1 * x;
  return x;
}

void get_x_y(const string& xy, int& x, int& y){
  string xy_string(xy);
  xy_string.replace(xy.find(','), 1, 1, ' ');
  istringstream iss(xy_string);
  iss >> x >> y;
}

void print_maze(vector< pair<int,int> > with_path = vector< pair<int,int> >()){
  cout << endl;
  map< pair<int, int>, bool > v;
  
  if(with_path.size() > 0){
    for(vector< pair<int,int> >::iterator i = with_path.begin(); i != with_path.end(); i++){
      v.insert(make_pair(make_pair(i->first, i->second),true));
    }
  }
			   
  for(int y = 0; y != maze.size(); y++){
    for(int x = 0; x != maze[0].size(); x++){
      char c;
      if( sx == x && sy ==  y)
	c = 'S';
      else if( ex == x && ey == y)
	c = 'E';
      else{ 
	c = maze[y][x] == -1 ? 'N' : '*';
	if(v.size() > 0 && v.find(make_pair(x,y)) != v.end() ){
	  c = 'P';
	}
      }
      cout << c << "  ";
    }
    cout << endl;
  }
}

template < class T > 
class my_queue {
private:
  queue<T> q;

public:
  void push(const T& x){
    q.push(x);
  }

  void pop(){
    q.pop();
  }

  bool empty(){
    return q.empty();
  }

  T top(){
    return q.front(); 
  }
};

class SearchNode{
public:
  int x,y, cost;
  vector< pair<int, int> > path_so_far;

  friend ostream& operator<<(ostream& output, const SearchNode& p);

  SearchNode(int x_, int y_, const vector< pair<int,int> > &  path_so_far_ , int cost_ = 1):
    x(x_),
    y(y_),
    path_so_far(path_so_far_),
    cost(cost_)
  {
    path_so_far.push_back(make_pair(x,y));
  }

  SearchNode(const SearchNode& other){
    x = other.x;
    y = other.y;
    cost = other.cost;
    path_so_far = other.path_so_far;
  }

  void print_path() const {
   for(vector< pair<int,int> >::const_iterator i = path_so_far.begin(); i != path_so_far.end(); i++){
	cout << endl << "(" << i->first << " , " << height - 1 - i->second << ")";
    }
    print_maze(path_so_far);
  }

};

ostream& operator<< (ostream& output, const SearchNode& p) {
  output <<  p.x << " " << p.y << " " << p.cost;
  return output;
}


#define UTIL_H
#endif
