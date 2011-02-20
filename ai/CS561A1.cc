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
bool enable_debug;
bool show_graph;

bool operator < (const SearchNode & left, const SearchNode & right){
  if(enable_debug){
    cout << endl << left << " : " << right;
    if( left.cost > right.cost )
      cout << endl << left << " > " << right;
    else
      cout << endl << right << " > " << left;
  }
  return left.cost > right.cost;
}

template <typename container>
void search(SearchStrategy<container> & search_strategy){
  bool found = false;

  while(search_strategy.should_search_more()){
    SearchNode p = search_strategy.get_next_search_node();

    if(enable_debug)
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

#define DFS_STRING_OPTION "-DFS"
#define BFS_STRING_OPTION "-BFS"
#define ASTAR_STRING_OPTION "-Astar"
#define UCS_STRING_OPTION "-UCS"

#define ALTERNATE_HUERISTIC_OPTION "-AltH"
#define ALTERNATE_COST_OPTION "-AltC"

#define DEBUG_OPTION "-D"
#define GRAPH_OTPION "-graph"

int main(int argc, char** argv){
  string file_name;
  int strategy = -1;
  bool use_my_hueristic = false;
  bool use_bottom_favoring_cost = false;
  enable_debug = false;
  show_graph = false;

  if(argc > 1){
    int i = 1;
    while(i < argc){
      string option = argv[i];

      if( DFS_STRING_OPTION == option )
	strategy = DFS_STRATEGY;
      else if( ASTAR_STRING_OPTION == option )
	strategy = A_STAR_STRATEGY;
      else if( BFS_STRING_OPTION == option )
	strategy = BFS_STRATEGY;
      else if( UCS_STRING_OPTION == option )
	strategy = UCS_STRATEGY;
      else if( ALTERNATE_HUERISTIC_OPTION == option )
	use_my_hueristic = true;
      else if( ALTERNATE_COST_OPTION == option )
	use_bottom_favoring_cost = true;
      else if( DEBUG_OPTION == option)
	enable_debug = true;
      else if( GRAPH_OTPION == option)
	show_graph = true;
      else 
	file_name = option;

    i++;
    }
  }

  if(strategy < 0){
    cerr << endl << "Unrecognized command option ";
    return -1;
  }

  ifstream file(file_name.c_str());
  if(!file.good()){
    cerr << endl << "Error opening file : " << file_name;
    return -1;
  }

  string line, part;

  width = height = 0;
  sx = sy = ex = ey = 0;

  if(file.is_open()){
    getline(file, line);
    
    if(enable_debug)
      cout << endl << line;
    
    get_x_y(line, width, height);
    
    if(enable_debug)
      cout << endl << width << " " << height;

    for(int h =0; h < height;h++){
      maze.push_back(vector<int>(width, 0));
    }

    getline(file, line);
    
    if(enable_debug)
      cout << endl << line;

    get_x_y(line, sx, sy);
    sy = height - 1 - sy;

    if( enable_debug)
      cout << endl << sx << " " << sy;

    getline(file, line);
    
    if(enable_debug)
      cout << endl << line;

    get_x_y(line, ex, ey);
    ey = height -1 -ey;
    
    if( enable_debug)
      cout << endl << ex << " " << ey;
    
    while(file.good()){
      getline(file, line);
      if(0 == line.length())
	break;
      
      if(enable_debug)
	cout << endl << line;
      
      get_x_y(line, x, y);
      
      if(enable_debug)
	cout << endl << x  << " " << y;
      
      if( -1 == x && -1 == y)
	continue;

      maze[height - 1 - y][x] = -1;
    }
  }

  if(enable_debug)
    print_maze();

  if( DFS_STRATEGY == strategy){
    DFS< stack< SearchNode > > dfs(sx, sy, ex, ey, width, height);
    search(dfs);
  }else if( A_STAR_STRATEGY == strategy ){
    if (use_my_hueristic){
      if( use_bottom_favoring_cost ){
	AStar< priority_queue< SearchNode > , MyHueristic , BottomFavoringCost > astar1(sx, sy, ex, ey, width, height);
	search(astar1);
      }else{
	AStar< priority_queue< SearchNode > , MyHueristic , UnitCostFunction > astar2(sx, sy, ex, ey, width, height);
	search(astar2);
      }
    }
    else{
      if( use_bottom_favoring_cost ){
	AStar< priority_queue< SearchNode > , Hueristic, BottomFavoringCost > astar3(sx, sy, ex, ey, width, height);
	search(astar3);
      }else{
	AStar< priority_queue< SearchNode > , Hueristic, UnitCostFunction > astar4(sx, sy, ex, ey, width, height);
	search(astar4);
      }
    }
  }else if( BFS_STRATEGY == strategy ){
    BFS< my_queue< SearchNode > > bfs(sx, sy, ex, ey, width, height);
    search(bfs);
  }else if( UCS_STRATEGY == strategy ){
    if( use_bottom_favoring_cost ){
      UniformCost< priority_queue< SearchNode > , BottomFavoringCost > ucs(sx, sy, ex, ey, width, height);
      search(ucs);
    }else {
      UniformCost< priority_queue< SearchNode > , UnitCostFunction > ucs1(sx, sy, ex, ey, width, height);
      search(ucs1);
    }
  }

  file.close();
  return 0;
}
