#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <map>
#include <queue>
#include <list>

#include <string>
#include <sstream>
#include <cctype>
#include <cmath>

#include "utility.cpp"

using namespace std;
using namespace my;

/*
Problem Statement


You are given a rectangular board containing m x n squares. Some squares on it are missing.

You must color the existing squares white or black, so that the number of black squares is maximized, and no two existing squares of the same color have a common side.

You are given the board as a String[] board, where the j-th character of the i-th element represents the square at row i, column j. Missing squares are denoted by '.' (dot) and existing squares are denoted by '#' (sharp). Return a String[] in the same format, where all '#' characters are replaced with lowercase 'w' for white squares and 'b' for black squares. If there are multiple solutions, return the one among them that comes first lexicographically. That is, you must minimize the first string, if there are still several solutions, minimize the second one, and so on.

Definition

Class:	MoreBlack
Method:	color
Parameters:	String[]
Returns:	String[]
Method signature:	String[] color(String[] board)
(be sure your method is public)


Constraints
-	board will contain between 1 and 50 elements, inclusive.
-	Each element of board will contain between 1 and 50 characters, inclusive.
-	All elements of board will contain the same number of characters.
-	Each element of board will contain only '.' and '#' characters.

Examples
0)


{".#.", "###", ".#."}

Returns: {".b.", "bwb", ".b." }

1)


{"#.#.#.", ".#.#.#", "#.#.#.", ".#.#.#", "#.#.#.", ".#.#.#"}

Returns: {"b.b.b.", ".b.b.b", "b.b.b.", ".b.b.b", "b.b.b.", ".b.b.b" }

2)


{"######"}

Returns: {"bwbwbw" }

3)


{".#.", ".#.", "###", ".#."}

Returns: {".w.", ".b.", "bwb", ".b." }
*/


/*
	Author : Karan Singh
	Email : karan.jude@gmail.com

	Logic : choose black as your 1 st color , then greedily fill all the neighbors
	        now choose white as ur 1 st color , then greedily fill all the nighbors
			now with two answers available check , which has a higher black value and
			return that
*/

class MoreBlack{
public:
	void color_neighbors(vector<string>& board,int i,int j,int m,int n,char color){
		board[i][j] = color;
		int dx[] = {-1,0,1,0};
		int dy[] = {0,-1,0,1};
		for(int k = 0;k < 4;k++){
			int x = j + dx[k];
			int y = i + dy[k];
			if(x < 0 || x >= n || y < 0 || y >= m) continue;
			char b = board[y][x] ;
			if(b == '#'){
				if(color == 'b')
					color_neighbors(board,y,x,m,n,'w');
				else
					color_neighbors(board,y,x,m,n,'b');
			}

		}
	}

	void color_board(vector<string> & board,char color){
		int m = board.size();
		int n = board.at(0).size();
		for(int i = 0;i < m;i++){
			for(int j = 0;j < n;j++){
				if(board[i][j] == '.') continue;
				if(board[i][j] == '#'){
					color_neighbors(board,i,j,m,n,color);
				}
			}
		}

	}

	int black_value(vector<string> & board){
		int sum = 0;
		for(int i =0; i < board.size(); i++){
			for(int j = 0;j < board.at(0).size();j++){
				if(board[i][j] == 'b')
					sum++;
			}
		}
		return sum;
	}

	vector<string> color(vector<string> board){
		vector<string> b(board);
		vector<string> w(board);
		color_board(b,'b');
		color_board(w,'w');
		if(black_value(w) > black_value(b))
			return w;
		return b;
	}
};


int main(){

MoreBlack b;

string s[] = {".#.", "###", ".#."};
string r[] = {".b.", "bwb", ".b." };
are_equal<string>(to_vector<string,3>(r),b.color(to_vector<string,3>(s)));

string s1[] = {"#.#.#.", ".#.#.#", "#.#.#.", ".#.#.#", "#.#.#.", ".#.#.#"};
string r1[] = {"b.b.b.", ".b.b.b", "b.b.b.", ".b.b.b", "b.b.b.", ".b.b.b" };
are_equal<string>(to_vector<string,6>(r1),b.color(to_vector<string,6>(s1)));

string s2[] = {"######"};
string r2[] = {"bwbwbw" };
are_equal<string>(to_vector<string,1>(r2),b.color(to_vector<string,1>(s2)));

string s3[] = {".#.", ".#.", "###", ".#."};
string r3[] = {".w.", ".b.", "bwb", ".b." };
are_equal<string>(to_vector<string,4>(r3),b.color(to_vector<string,4>(s3)));


int number;
	cin >> number;
	return 0;
}