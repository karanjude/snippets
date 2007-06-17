//328000

#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <cctype>
#include <set>
#include <list>

#include <utility.cpp>

using namespace std;

// 1000 char u get x
// y pages produce
// 25 working days


const int VAL = 328000;
class Bees {
	
public :
	int maxProfit(int profit_percentage , int price_per_thousand_characters , int thousand_chars_per_page){
		int what_u_want = ((profit_percentage * VAL / 100)) + VAL;
		//cout << endl << endl << "what u want : " << what_u_want;
		int pages_u_need_to_produce = what_u_want / ( thousand_chars_per_page * price_per_thousand_characters); 
		return pages_u_need_to_produce;
	}
};


int _tmain(int argc, _TCHAR* argv[]){
	Bees b;
	
	for(int p = 8;p <= 30 ; p++){
		for(int pp = 8; pp <= 12;pp++){
			int v = b.maxProfit(p,pp,2);
			cout << endl << "for profit margin " << p << " price per thousand characters : " << pp << " output needs to be : " << v;
		}
	}

	int ii;
	cin >> ii;
	return 0;
}