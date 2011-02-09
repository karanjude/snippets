#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <stack>
#include <map>

using namespace std;

vector< vector<int> > maze;
int x,y, width, height, sx, sy, ex, ey;
map< pair<int, int>, bool > visited;


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

struct node{
  int x,y;
  vector< pair<int, int> > path_so_far;

  node(int x_, int y_, const vector< pair<int,int> > &  path_so_far_):
    x(x_),
    y(y_),
    path_so_far(path_so_far_)
  {
    path_so_far.push_back(make_pair(x,y));
  }

  node(const node& other){
    x = other.x;
    y = other.y;
    path_so_far = other.path_so_far;
  }
};
	    
	   

void dfs(){
  stack< node > s;
  s.push(node(sx,sy, vector< pair<int,int> >()));
  
  int dx[] = {-1,1,0,0};
  int dy[] = {0,0,-1,1};
  
  while(!s.empty()){
    node p = s.top();
    s.pop();

    cout << endl << "processing .. " << p.x << " " << p.y;

    if(visited.find(make_pair(p.x, p.y)) != visited.end())
       continue;

    visited.insert(make_pair(make_pair(p.x, p.y) ,true));

    if(ex == p.x && ey == p.y){
      cout << endl << "FOUND DESTINATION";
      for(vector< pair<int,int> >::iterator i = p.path_so_far.begin(); i != p.path_so_far.end(); i++){
	cout << endl << "(" << i->first << " , " << height - 1 - i->second << ")";
      }
      print_maze(p.path_so_far);
      break;
    }

    for(int i = 0; i < 4;i++){
      int xx = p.x + dx[i];
      int yy = p.y - dy[i];
      if (xx < 0 || xx > width-1 || yy < 0 || yy > height-1 )
	continue;
      
      cout << endl << "v : at " << xx << " " << yy << " " << maze[yy][xx];
      if (maze[yy][xx] < 0)
	continue;
      
      s.push(node(xx,yy, p.path_so_far));
      visited[make_pair(p.x, p.y)] = false;
    }
    
  }
		  
}

int main(int argc, char** argv){
  char * file_name = NULL;


  if(argc > 1)
    file_name = argv[1];

  ifstream file(file_name);
  string line, part;

  width = height = 0;
  sx = sy = ex = ey = 0;

  if(file.is_open()){
    getline(file, line);
    cout << endl << line;
    get_x_y(line, width, height);
    cout << endl << width << " " << height;

    for(int h =0; h < height;h++){
      maze.push_back(vector<int>(width, 0));
    }

    getline(file, line);
    cout << endl << line;
    get_x_y(line, sx, sy);
    sy = height - 1 - sy;
    cout << endl << sx << " " << sy;

    getline(file, line);
    cout << endl << line;
    get_x_y(line, ex, ey);
    ey = height -1 -ey;
    cout << endl << ex << " " << ey;
    
    while(file.good()){
      getline(file, line);
      if(0 == line.length())
	break;
      cout << endl << line;
      get_x_y(line, x, y);
      cout << endl << x  << " " << y;
      if( -1 == x && -1 == y)
	continue;

      maze[height - 1 - y][x] = -1;
    }
  }

  print_maze();
  dfs();

  file.close();
  return 0;
}
