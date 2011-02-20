#ifndef ASTAR_H

#include "strategy.h"

class Hueristic {
 public:
  int hueristic(int sx, int sy, int ex, int ey){
    int dx = abs(sx - ex);
    int dy = abs(sy - ey);
    int v = dx + dy;

    if (enable_debug)
      cout << endl << "HEURISTIC :"<<  sx << " : " << sy << " " << ex << " " << ey << " " << dx << " " << dy << " " << v;

    return v;
  }
};

class MyHueristic : public Hueristic {
 public:
  int hueristic(int sx, int sy, int ex, int ey){
    int dx = abs(sx - ex);
    int dy = abs(sy - ey);
    int v = max(dx,dy);
    return v;
  }
};

template<typename container, typename hueristictype, typename coststrategy>  
class AStar : public SearchStrategy<container> {
 private:
  hueristictype hueristic_function;
  coststrategy coststrategy_;
  int initial_hueristic_cost;

  public:
  AStar(int start_x_, int start_y_, int end_x_, int end_y_, int width__, int height__):
    SearchStrategy<container>(start_x_, start_y_, end_x_, end_y_, width__, height__, 
			      hueristic_function.hueristic(start_x_, start_y_, end_x_, end_y_))
      {
	initial_hueristic_cost = hueristic_function.hueristic(start_x_, start_y_, end_x_, end_y_);
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

    virtual void extra_print(){
      cout << endl << "Estimated Cost (by heuristic function): " << initial_hueristic_cost;
    }
							    
    virtual int cost(const SearchNode& p, int xx, int yy, int ex, int ey){
      int c = coststrategy_.cost(p);
      int cost = c - hueristic_function.hueristic(p.x, p.y, ex, ey) + hueristic_function.hueristic(xx, yy , ex, ey);
      return cost;
    }
  
};


#define ASTAR_H
#endif
