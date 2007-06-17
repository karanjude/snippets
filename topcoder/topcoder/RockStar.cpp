#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <cctype>
#include <string>
#include <utility.cpp>

using namespace std;

class RockStar{
	int _ff , _fs , _sf , _ss;
	void ff(){
		_ff--;
		while(_ff > 0 ) _ff--;
		if(_fs > 0 && _fs > _ff) fs();
	}

	void fs(){
		_fs--;
		if(_ss > 0 ) ss();
		if(_sf > 0 && _sf > _ss) sf();
	}

	void sf(){
		_sf--;
		if(_ff > 0 ) ff();
		if(_fs > 0 && _fs > _ff) fs();
	}

	void ss(){
		_ss--;
		while(_ss > 0 ) _ss--;
		if(_sf > 0 && _sf > _ss) sf();
	}

public:
	/*int getNumSongs(int __ff,int __fs,int __sf,int __ss){
		_ff = __ff;_fs = __fs;_sf = __sf;_ss = __ss;
		if(_ff == 0 && _fs != 0 ) fs();
		else if(_fs == 0 && _ff != 0 ) ff();
		else if(_ff != 0 && _fs != 0){
			if(_ff >= _fs)			
				ff();
			else
				fs();
		}
		else if(_fs == 0 && _ff == 0){
			if(_sf > 0 && _sf >= _ss) sf();
			else if(_ss > 0 && _ss >= _sf) ss();
		}
		int songs = 0;
		songs +=  __ff - _ff;
		songs +=  __fs - _fs;
		songs += __sf - _sf;
		songs += __ss - _ss;
		return songs;
	}*/
	int getNumSongs(int ff, int fs, int sf, int ss) { 
    // !FDI 
    if(ff == 0 && fs == 0) return ss + (sf ? 1 : 0); 
    else if(fs == 0) return ff; 
    else if(sf < fs) return ff + ss + (sf+1) + sf; 
    else return ff + ss + fs + fs; 
    } 

};

int _tmain(int argc, _TCHAR* argv[]){

   RockStar r;
   are_equal_with_print<int>(5,r.getNumSongs(1,2,1,1));
   are_equal_with_print<int>(100,r.getNumSongs(100,0,0,200));
   are_equal_with_print<int>(201,r.getNumSongs(0,0,20,200));
   are_equal_with_print<int>(999,r.getNumSongs(192,279,971,249));
   are_equal_with_print<int>(4000,r.getNumSongs(1000,1000,1000,1000));
	int ii;
	cin >> ii;
	return 0;
}