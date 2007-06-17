#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <map>
#include <algorithm>

#include <utility.cpp>


using namespace std;

int bomber_man_dx[4] = {0 ,1,0,-1};
int bomber_man_dy[4] = {-1,0,1,0};

int bomber_man_maze[50][50];

struct Node{
	Node(int x,int y,int time_taken,int bombs_left){
		this->x = x;
		this->y = y;
		this->time_taken = time_taken;
		this->bombs_left = bombs_left;
	}

	int x;
	int y;
	int time_taken;
	int bombs_left;
};

bool operator < (const Node &left , const Node &right){
	return left.time_taken > right.time_taken;
}

class BombMan{
private:
	int start_x , start_y , end_x , end_y;	
	int max_x,max_y;
	int number_of_bombs;
	map<pair<int,int>,int> visited;
	map<pair<int,int>,int>::iterator item;

	void initialize(){
		memset(bomber_man_maze,0,sizeof(bomber_man_maze));
		visited.clear();	
	}

	void pupulate_maze(vector<string> maze){
		for(int i = 0; i < maze.size() ; i++){
			max_y = maze.size();
			for(int j = 0;j < maze[i].length();j++){
				max_x = maze[i].length();
				switch(maze[i][j]){
					case '.' :
						bomber_man_maze[i][j] = 1;
						break;
					case '#' : 
						bomber_man_maze[i][j] = 0;
						break;
					case 'B' : 
						bomber_man_maze[i][j] = 3;
						start_x = j;
						start_y = i;
						break;
					case 'E' : 
						bomber_man_maze[i][j] = 1;
						end_x = j;
						end_y = i;
						break;
				}
			}
		}
	}

	bool is_valid(int x,int y){
		return !(x < 0 || y < 0 || x > max_x || y > max_y);
	}
public:
	int shortestPath(vector<string> maze, int bombs){
		initialize();
		pupulate_maze(maze);
		number_of_bombs = bombs;
		priority_queue<Node> q;
		q.push(Node(start_x,start_y,0,number_of_bombs));
		while(!q.empty()){
			Node current = q.top();q.pop();
			if(current.x == end_x && current.y == end_y){
				return current.time_taken;
			}
			if(visited.find(make_pair(current.x,current.y)) != visited.end() ) continue;

				visited.insert(make_pair(make_pair(current.x,current.y),current.time_taken));
			for(int i = 0;i < 4;i++){
				int x = current.x + bomber_man_dx[i];
				int y = current.y + bomber_man_dy[i];
				if(is_valid(x,y))
					if(bomber_man_maze[y][x] == 1)
						q.push(Node(x,y,current.time_taken + 1,current.bombs_left));
					else if(bomber_man_maze[y][x] == 0 && current.bombs_left > 0)
						q.push(Node(x,y,current.time_taken + 3,current.bombs_left - 1));
			}
		}
		return -1;
	}
};

int _tmain(int argc, _TCHAR* argv[]){
	
 string maze[] =	{".....B.",
					".#####.",
					".#...#.",
					".#E#.#.",
					".###.#.",
					"......."};

 BombMan b;
 are_equal_with_print<int>(8, b.shortestPath(to_vector<string,6>(maze),1));

 string maze1[] = {"..#####",
 "B.#####",
 "..#####",
 "#######",
 "####...",
 "####.E."};

 are_equal_with_print<int>(17, b.shortestPath(to_vector<string,6>(maze1),4));

 string maze2[] = {"B.#.#.#...E"};

 are_equal_with_print<int>(-1, b.shortestPath(to_vector<string,1>(maze2),2));

 string maze3[] = 
 {".#.#.#.#B#...#.#...#.#...#.#...#.#...#.#.#.......",
 ".#.#.#.#.#.###.###.#.###.#.#.###.###.#.#.#.###.##",
 ".#.#.#...#.#.#.#.#.#...#.....#.#.#...#...#.#.#...",
 ".#.#.###.#.#.#.#.#.###.#.#####.#.###.###.#.#.###.",
 ".............#.#...#...#.....#.#.#...#.#.#.....#.",
 "##.#######.###.#.#####.#.#####.#.###.#.#.#.#.####",
 ".#.#.....#...#...#.#...#...#.#.#...#...#...#.....",
 ".#######.#.#####.#.#.#.#.###.#.###.#.#####.#.####",
 ".#.#.#.#...#.#.#.#.#.#.......#...#.#...#.#.#.....",
 ".#.#.#.###.#.#.#.#.#####.#####.###.###.#.#.######",
 ".....#...#.#...#...#...#...#...#...#.#.#.........",
 "####.###.#.###.###.#.###.#.#.###.###.#.#.########",
 ".......#.........#.#.#.#.#.#.#.#.........#...#...",
 ".#.###.#########.#.#.#.#.###.#.#####.#.#.#.###.##",
 ".#.#.........#.#.#.#.#.....#.#.#.....#.#.........",
 "############.#.#.#.#.#.#####.#.#.################",
 ".#...........#...#.#.#.#...#.#.#...#.#.#.....#...",
 ".#####.#####.###.#.#.#.#.###.#.#.###.#.#.#####.##",
 ".......#...#.#.#.....#...#...#.#.#.#.#...........",
 "##########.#.#.#####.#.###.###.#.#.#.#.##########",
 ".....#...#.....#.#...#.......#.#...#.......#.....",
 "##.#.###.#.###.#.#.#.#.#####.#.#.###.#######.####",
 "...#...#...#.......#.....#.#...#...#.......#.....",
 "####.#.#.#########.#.###.#.#####.###.#.#######.##",
 ".#...#...#.........#.#.....#.........#.#.#.#.....",
 ".#####.#.#.###.#######.#.###.#.#########.#.#.####",
 ".......#.#.#...#.......#.....#.#.#.......#.#.#.#.",
 "########.#.#.#.#####.#.###.#.###.#.#######.#.#.#.",
 ".........#.#.#.#.....#...#.#.........#.#.........",
 "################.#.#.#.#.#.#.#.#######.#.########",
 ".................#.#.#.#.#.#.#...........#.......",
 "########.#####.#.###.#.#.#####.###.#.#####.###.##",
 ".........#...#.#...#.#.#...#.....#.#.........#...",
 ".#####.#####.#.###.#.###.#.#.#.#.#.#####.#.###.#.",
 ".#.....#.........#.#.#...#.#.#.#.#.#.....#...#.#.",
 "####.#####.###.#.#.#.#.#.#.###.###.#.#.#.#.#####.",
 ".....#.....#.#.#.#.#.#.#.#.#...#...#.#.#.#...#...",
 "####.#.#.###.#.#.###.#.###.#.#.#####.#.#.#.######",
 ".....#.#.#.#...#...#.#...#.#.#...#...#.#.#.......",
 "##########.#.#.#.#####.###.#.#.###.#.###.#####.##",
 "...#.#...#...#.#.....#.#...#.#...#.#.#.......#...",
 ".#.#.#.#.#.#.#.#.#.#.###.#.#########.###.#.#.#.#.",
 ".#.#...#...#.#.#.#.#...#.#...#.......#...#.#.#.#.",
 "##.###.#.#.###.#.#.#.#.#####.#.#.#.###.#.########",
 ".......#.#...#.#.#.#.#.#.....#.#.#...#.#.........",
 "####.#######.#.#####.#.###.#.#.###.#.#.#.########",
 "E..#.......#.#.....#.#.#.#.#.#.#...#.#.#.........",
 "##.#.#.#.###.###.###.###.#.#.###.#.#.#.#.#######.",
 ".....#.#...#.#.....#.#.....#...#.#.#.#.#.....#..."};

are_equal_with_print<int>(76, b.shortestPath(to_vector<string,49>(maze3),3));

    int i;
	cin >> i;
	return 0;
}