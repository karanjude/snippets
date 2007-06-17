/*

Problem Statement
    
People enjoy mazes, but they also get them dirty. Arrows, graffiti, and chewing gum are just a few of the souvenirs people leave on the walls. You, the maze keeper, are assigned to whiten the maze walls. Each face of the wall requires one liter of paint, but you are only required to paint visible faces. You are given a map of the maze, and you must determine the amount of paint needed for the job.
The maze is described by a vector <string> maze, where each character can be either '#' (a wall) or '.' (an empty space). All '.' characters on the perimeter of the map are considered entrances to the maze. Upon entering the maze, one can only move horizontally and vertically through empty spaces, and areas that are not reachable by these movements are not considered visible. Each '#' represents a square block with four wall faces (each side of the square is a face). A face is visible if it is not directly adjacent to another wall (and is in a reachable area of the maze). For example, two adjacent blocks can have at most six visible faces since two of their faces are directly adjacent to each other. All exterior faces on the perimeter are considered visible.
For example, the following picture represents a trivial maze with just one (wide) entrance and only four empty reachable spaces:  
 
To whiten this maze you must paint the faces highlighted in yellow above: 16 for its perimeter, plus 8 interior faces. Note that there are faces that are not visible and thus need not be painted.
Definition
    
Class:
TroytownKeeper
Method:
limeLiters
Parameters:
vector <string>
Returns:
int
Method signature:
int limeLiters(vector <string> maze)
(be sure your method is public)
    

Constraints
-
maze will contain between 1 and 50 elements, inclusive.
-
Each element of maze will contain between 1 and 50 characters, inclusive.
-
All elements of maze will have the same number of characters.
-
All characters in maze will be either '.' or '#'.
Examples
0)

    
{"##..#"
,"#.#.#"
,"#.#.#"
,"#####"}
Returns: 24
Example from the problem statement.
1)

    
{"##",
 "##"}
Returns: 8
Only the perimeter of the maze (which has no interior!) has to be painted.
2)

    
{"######"
,"#....."
,"#.####"
,"#.#..#"
,"#.##.#"
,"#....#"
,"######"}
Returns: 56

3)

    
{"######"
,"#....."
,"#..#.."
,"#....."
,"######"}
Returns: 36

4)

    
{"#.#.#.#"
,".#.#.#."
,"#.#.#.#"
,".#.#.#."}
Returns: 36

This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.
*/

#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <cctype>

#include <utility.cpp>

using namespace std;

int dx[4] = {0 ,1,0,-1};
int dy[4] = {-1,0,1,0};

static int _maze[50][50][4];

struct Node{
	Node(int x,int y){
		this->x = x;
		this->y = y;
	}
	int x;
	int y;
};


class TroytownKeeper{

private:
	queue<Node> q;
	int color_basic_walls_on_perimeter(vector<string> maze){
		int walls = 0;
		for(int j = 0; j < maze[0].length(); j++)
			if(maze[0][j] == '#')
				walls++;
			else
				q.push(Node(j,0));
		for(int j = 0;j < maze.size(); j++)
			if(maze[j][0] == '#')
				walls++;
			else
				q.push(Node(0,j));
		for(int j = 0;j < maze.size();j++)
			if(maze[j][maze[0].length()-1] == '#')
				walls++;
			else
				q.push(Node(maze[0].length()-1,j));
		for(int j = 0; j < maze[maze.size()-1].length(); j++)
			if(maze[maze.size()-1][j] == '#')
				walls++;
			else
				q.push(Node(j,maze.size()-1));
		return walls;
	}

	void initialize(){
		memset(_maze,0,sizeof(_maze));
	}
public:
	int limeLiters(vector <string> maze){
		initialize();
		int maxx = maze[0].length() -1;
		int maxy = maze.size() -1;
		int visited_walls = 0;
		int walls =  color_basic_walls_on_perimeter(maze);
		while(!q.empty()){
			Node top = q.front();
			q.pop();
			int x = top.x;
			int y = top.y;
			if(_maze[y][x][0]) continue;
			else {
				_maze[y][x][0] = _maze[y][x][1] = _maze[y][x][2] = _maze[y][x][3] = 1;	
			}
			for(int i = 0;i < 4;i++){
				int xx = x + dx[i];
				int yy = y + dy[i];
				if(xx < 0 || xx > maxx || yy < 0 || yy > maxy ) continue;
				if(maze[yy][xx] == '.')
					q.push(Node(xx,yy));
				else{
					if(!_maze[yy][xx][i]){ 
						_maze[yy][xx][i] = 1;
						visited_walls++;
					}
				}
			}

		}
		return walls + visited_walls;
	}
};

int _tmain(int argc, _TCHAR* argv[]){

	TroytownKeeper t;
	string w[] = {"##", "##"};
	are_equal_with_print<int>(8, t.limeLiters(to_vector<string,2>(w)));

	string w1[] =	{"##..#"
					,"#.#.#"
					,"#.#.#"
					,"#####"};
	are_equal_with_print<int>(24,t.limeLiters(to_vector<string,4>(w1)));

	string w2[] = {"######"
,"#....."
,"#.####"
,"#.#..#"
,"#.##.#"
,"#....#"
,"######"};
are_equal_with_print<int>(56,t.limeLiters(to_vector<string,7>(w2)));

string w3[] = {"######"
,"#....."
,"#..#.."
,"#....."
,"######"};
are_equal_with_print<int>(36,t.limeLiters(to_vector<string,5>(w3)));

string w4[] = 
{"#.#.#.#"
,".#.#.#."
,"#.#.#.#"
,".#.#.#."};
are_equal_with_print<int>(36,t.limeLiters(to_vector<string,4>(w4)));


	int ii;
	cin >> ii;
	return 0;
}