#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <stack>
#include <map>
#include <queue>

using namespace std;

vector< vector<int> > maze;
int x,y, width, height, sx, sy, ex, ey;
map< pair<int, int>, bool > visited;

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


ostream& operator<<(ostream& output, const SearchNode& p) {
  output <<  p.x << " " << p.y << " " << p.cost;
  return output;
}

bool operator < (const SearchNode & left, const SearchNode & right){
  
  cout << endl << left << " : " << right;
  if( left.cost > right.cost )
    cout << endl << left << " > " << right;
  else
    cout << endl << right << " > " << left;
  return left.cost > right.cost;
}

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
      
	cout << endl << "v : at " << xx << " " << yy << " " << maze[yy][xx];
	if (maze[yy][xx] < 0)
	  continue;
	
	int c = cost(p, xx, yy, end_x, end_y);

	if(!should_discard(p, c)){
	  cout << endl << "adding " << xx << " " << yy;
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

  virtual void process_end_node(const SearchNode& p){
    cout << endl << "FOUND DESTINATION";
    p.print_path();
    cout << endl << "nodes seen : " << SearchStrategy<container>::nodes_seen;
    cout << endl << "path cost : " << p.path_so_far.size();
  }

};

template<typename container>
class DFS : public SearchStrategy<container> {
  public:
  DFS(int start_x_, int start_y_, int end_x_, int end_y_, int width__, int height__):
      SearchStrategy<container>(start_x_, start_y_, end_x_, end_y_, width__, height__)
    {
    }
  
  virtual void unmark_node(const SearchNode& p){
    visited[make_pair(p.x, p.y)] = false;
  }
  
  virtual bool can_generate_search_node_at(int xx , int yy){
    return xx < 0 || xx > SearchStrategy<container>::width_ - 1 || yy < 0 || yy > SearchStrategy<container>::height_ -1;
  }

};

template<typename container>
class BFS : public SearchStrategy<container> {
  public:
  BFS(int start_x_, int start_y_, int end_x_, int end_y_, int width__, int height__):
      SearchStrategy<container>(start_x_, start_y_, end_x_, end_y_, width__, height__)
    {
    }
  
  virtual void unmark_node(const SearchNode& p){
    visited[make_pair(p.x, p.y)] = false;
  }
  
  virtual bool can_generate_search_node_at(int xx , int yy){
    return xx < 0 || xx > SearchStrategy<container>::width_ - 1 || yy < 0 || yy > SearchStrategy<container>::height_ -1;
  }

};


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

template<typename container>  
class UniformCost : public SearchStrategy<container> {
  public:
  UniformCost(int start_x_, int start_y_, int end_x_, int end_y_, int width__, int height__):
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
    int cost = p.cost + 1;
    return cost;
  }
  
};


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
