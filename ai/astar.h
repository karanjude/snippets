#ifndef ASTAR_H

#include "strategy.h"

template<typename container>  
class AStar : public SearchStrategy<container> {
  public:
  AStar(int start_x_, int start_y_, int end_x_, int end_y_, int width__, int height__):
    SearchStrategy<container>(start_x_, start_y_, end_x_, end_y_, width__, height__, 
			      hueristic(start_x_, start_y_, end_x_, end_y_))
  {
  }

  virtual bool can_generate_search_node_at(int xx , int yy){
    return xx < 0 || xx > SearchStrategy<container>::width_ - 1 || yy < 0 || yy > SearchStrategy<container>::height_ -1;
  }

  virtual void unmark_node(const SearchNode& p){
    visited[make_pair(p.x, p.y)] = false;
  }

  virtual bool should_discard(const SearchNode& p, int cost){
    return cost < p.cost;
  }
							    

  int hueristic(int sx, int sy, int ex, int ey){
    int dx = abs(sx - ex);
    int dy = abs(sy - ey);
    int v = dx + dy;
    cout << endl << "HEURISTIC :"<<  sx << " : " << sy << " " << ex << " " << ey << " " << dx << " " << dy << " " << v;
    return v;
  }
  
  virtual int cost(const SearchNode& p, int xx, int yy, int ex, int ey){
    int cost = p.cost - hueristic(p.x, p.y, ex, ey) + 1   + hueristic(xx, yy , ex, ey);
    return cost;
  }
  
};


#define ASTAR_H
#endif
