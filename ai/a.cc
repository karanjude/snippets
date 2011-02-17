#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <stack>
#include <map>
#include <queue>

#include "util.h"
#include "strategy.h"
#include "dfs.h"
#include "bfs.h"
#include "astar.h"
#include "ucs.h"

using namespace std;

vector< vector<int> > maze;
int x,y, width, height, sx, sy, ex, ey;
map< pair<int, int>, bool > visited;


bool operator < (const SearchNode & left, const SearchNode & right){
  cout << endl << left << " : " << right;
  if( left.cost > right.cost )
    cout << endl << left << " > " << right;
  else
    cout << endl << right << " > " << left;
  return left.cost > right.cost;
}

template <typename container>
void search(SearchStrategy<container> & search_strategy){
  bool found = false;

  while(search_strategy.should_search_more()){
    SearchNode p = search_strategy.get_next_search_node();

    cout << endl << "processing .. " << p.x << " " << p.y;
   
    if(!search_strategy.should_process_node(p))
      continue;

    search_strategy.mark_node(p);
    if(search_strategy.has_reached_goal_node(p)){
      search_strategy.process_end_node(p);
      found = true;
      break;
    }
    search_strategy.generate_search_nodes(p);
    search_strategy.unmark_node(p);
  }

  if(!found){
    print_maze();
    cout << endl << "NO SOLUTION";
  }
}	   

enum { DFS_STRATEGY, BFS_STRATEGY, A_STAR_STRATEGY , UCS_STRATEGY};

int main(int argc, char** argv){
  char * file_name = NULL;
  int strategy = 0;

  if(argc > 1){
    file_name = argv[1];
    if ( argc >= 2){
      string strategy_string = argv[2];
      if( "dfs" == strategy_string )
	strategy = DFS_STRATEGY;
      else if( "astar" == strategy_string )
	strategy = A_STAR_STRATEGY;
      else if( "bfs" == strategy_string )
	strategy = BFS_STRATEGY;
      else if( "ucs" == strategy_string )
	strategy = UCS_STRATEGY;

    }
  }

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

  if( DFS_STRATEGY == strategy){
    DFS< stack< SearchNode > > dfs(sx, sy, ex, ey, width, height);
    search(dfs);
  }else if( A_STAR_STRATEGY == strategy ){
    AStar< priority_queue< SearchNode > > astar(sx, sy, ex, ey, width, height);
    search(astar);
  }else if( BFS_STRATEGY == strategy ){
    BFS< my_queue< SearchNode > > bfs(sx, sy, ex, ey, width, height);
    search(bfs);
  }else if( UCS_STRATEGY == strategy ){
    UniformCost< priority_queue< SearchNode > > ucs(sx, sy, ex, ey, width, height);
    search(ucs);
  }

  file.close();
  return 0;
}
