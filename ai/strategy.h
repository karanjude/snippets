#ifndef STRATEGY_H

#include <map>
#include <vector>

#include "util.h"

using namespace std;

template< typename container >
class SearchStrategy{
  
protected:
  container s;
  int start_x, start_y, end_x, end_y;
  map< pair<int, int>, bool > visited;
  int nodes_seen, path_cost;
  int width_, height_;
  
public:
  SearchStrategy(int start_x_, int start_y_, int end_x_, int end_y_, int width__, int height__, int cost_ = 0):
    start_x(start_x_),
    start_y(start_y_),
    end_x(end_x_),
    end_y(end_y_),
    nodes_seen(0),
    path_cost(0),
    width_(width__),
    height_(height__)
  {
    s.push(SearchNode(start_x, start_y, vector< pair<int,int> >(), cost_));
  }

  virtual bool should_search_more(){
    return !s.empty();
  }

  virtual SearchNode get_next_search_node(){
    SearchNode node = s.top();
    s.pop();
    return node;
  }

  virtual bool has_reached_goal_node(const SearchNode& p){
    return (end_x == p.x && end_y == p.y);
  }

  virtual bool can_generate_search_node_at(int xx , int yy){
    return xx < 0 || xx > width_ - 1 || yy < 0 || yy > height_ -1;
  }

  virtual int cost(const SearchNode& p, int xx, int yy, int ex, int ey){
    return 0;
  }
  
  virtual void generate_search_nodes(const SearchNode& p){
    int dx[] = {-1,1,0,0};
      int dy[] = {0,0,-1,1};

      for(int i = 0; i < 4;i++){
	int xx = p.x + dx[i];
	int yy = p.y - dy[i];
	if(can_generate_search_node_at(xx, yy))
	  continue;
      
	if(enable_debug)
	  cout << endl << "v : at " << xx << " " << yy << " " << maze[yy][xx];
	
	if (maze[yy][xx] < 0)
	  continue;
	
	int c = cost(p, xx, yy, end_x, end_y);

	if(!should_discard(p, c)){
	  s.push(SearchNode(xx,yy, p.path_so_far, c ));
	}
      }
      
  }
  
  virtual bool should_discard(const SearchNode& p, int cost){
    return false;
  }

  virtual bool should_process_node(const SearchNode& p){
    return visited.find(make_pair(p.x, p.y)) == visited.end();
  }

  virtual void mark_node(const SearchNode& p){
    visited.insert(make_pair(make_pair(p.x, p.y) ,true));
    nodes_seen++;
    if((p.x == start_x && p.y == start_y) || (p.x == end_x && p.y == end_y))
      nodes_seen--;
  }
  
  virtual void unmark_node(const SearchNode& p){
    visited[make_pair(p.x, p.y)] = false;
  }

  virtual void extra_print(){
  }

  virtual void process_end_node(const SearchNode& p){
    cout << endl << "Found Path";

    p.print_path();

    extra_print();
    cout << endl << "Nodes Expanded: " << SearchStrategy<container>::nodes_seen;
    cout << endl << "Nodes on Path: " << p.path_so_far.size();
    cout << endl << "Ratio: " << float(SearchStrategy<container>::nodes_seen) / float(p.path_so_far.size());
  }

};


template<class T>
class CostFunction {
 public:
  virtual T cost(const SearchNode& p) = 0;
};

class UnitCostFunction: public CostFunction<int> {
 public:
  virtual int cost(const SearchNode& p){
    int cost_ = p.cost + 1;
    return cost_;
  }
}; 

class BottomFavoringCost: public CostFunction<int> {
 public:
  virtual int cost(const SearchNode& p){
    int cost_ = p.cost + 1 + (.1 * (height - 1 - p.y));
    return cost_;
  }
};


#define STRATEGY_H
#endif

