#ifndef UCS_H

#include "strategy.h"

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

template<typename container, typename coststrategy>  
class UniformCost : public SearchStrategy<container> {
 private:
  coststrategy cost_function_;

  public:
 UniformCost(int start_x_, int start_y_, int end_x_, int end_y_, int width__, int height__
	     ):
    SearchStrategy<container>(start_x_, start_y_, end_x_, end_y_, width__, height__)
  {
  }

  virtual bool can_generate_search_node_at(int xx , int yy){
    return xx < 0 || xx > SearchStrategy<container>::width_ - 1 || yy < 0 || yy > SearchStrategy<container>::height_ -1;
  }
  
  virtual void unmark_node(const SearchNode& p){
    visited[make_pair(p.x, p.y)] = false;
  }

  virtual int cost(const SearchNode& p, int xx, int yy, int ex, int ey){
    return cost_function_.cost(p);
  }
  
};



#define UCS_H
#endif
