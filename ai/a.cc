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

class SearchNode{
public:
  int x,y;
  vector< pair<int, int> > path_so_far;

  SearchNode(int x_, int y_, const vector< pair<int,int> > &  path_so_far_ ):
    x(x_),
    y(y_),
    path_so_far(path_so_far_)
  {
    path_so_far.push_back(make_pair(x,y));
  }

  SearchNode(const SearchNode& other){
    x = other.x;
    y = other.y;
    path_so_far = other.path_so_far;
  }

  void print_path() const {
   for(vector< pair<int,int> >::const_iterator i = path_so_far.begin(); i != path_so_far.end(); i++){
	cout << endl << "(" << i->first << " , " << height - 1 - i->second << ")";
    }
    print_maze(path_so_far);
  }

};


  class SearchStrategy{
  public:
    virtual bool should_search_more() = 0;
    virtual SearchNode get_next_search_node() = 0;
    virtual bool has_reached_goal_node(const SearchNode& ) = 0;
    virtual bool can_generate_search_node_at(int x, int y) = 0;
    virtual void generate_search_nodes(const SearchNode& ) = 0;
    virtual bool should_process_node(const SearchNode& ) = 0;
    virtual void mark_node(const SearchNode& ) = 0;
    virtual void unmark_node(const SearchNode& ) = 0;
    virtual void process_end_node(const SearchNode& ) = 0;
  };

  class DFS : public SearchStrategy {
  private:
    stack<SearchNode> s;
    map< pair<int, int>, bool > visited;
    int start_x, start_y, end_x, end_y;
    
  public:
    DFS(int start_x_, int start_y_, int end_x_, int end_y_):
      start_x(start_x_),
      start_y(start_y_),
      end_x(end_x_),
      end_y(end_y_)
    {
      s.push(SearchNode(start_x, start_y, vector< pair<int,int> >()));
    }

    bool should_search_more(){
      return !s.empty();
    }

    SearchNode get_next_search_node(){
      SearchNode node = s.top();
      s.pop();
      return node;
    }

    bool should_process_node(const SearchNode& p){
      return visited.find(make_pair(p.x, p.y)) == visited.end();
    }

    void mark_node(const SearchNode& p){
      visited.insert(make_pair(make_pair(p.x, p.y) ,true));
    }

    bool has_reached_goal_node(const SearchNode& p ){
      return (end_x == p.x && end_y == p.y);
    }

    void process_end_node(const SearchNode& p){
      cout << endl << "FOUND DESTINATION";
      p.print_path();
    }

    void unmark_node(const SearchNode& p){
      visited[make_pair(p.x, p.y)] = false;
    }

    bool can_generate_search_node_at(int xx , int yy){
      return xx < 0 || xx > width-1 || yy < 0 || yy > height-1;
    }

    void generate_search_nodes(const SearchNode& p){
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
      
	s.push(SearchNode(xx,yy, p.path_so_far));
	//visited[make_pair(p.x, p.y)] = false;
      }
    }

  };
	  
void search(SearchStrategy& search_strategy){
  while(search_strategy.should_search_more()){
    SearchNode p = search_strategy.get_next_search_node();

    cout << endl << "processing .. " << p.x << " " << p.y;
   
    if(!search_strategy.should_process_node(p))
      continue;

    search_strategy.mark_node(p);
    if(search_strategy.has_reached_goal_node(p)){
      search_strategy.process_end_node(p);
      break;
    }
    search_strategy.generate_search_nodes(p);
    search_strategy.unmark_node(p);
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

  DFS dfs(sx, sy, ex, ey);
  search(dfs);

  file.close();
  return 0;
}
