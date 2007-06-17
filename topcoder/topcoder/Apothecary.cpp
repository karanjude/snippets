#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>
#include <list>
#include <string>
#include <cctype>
#include <string>
#include <utility.cpp>
#include <cmath> 

using namespace std;

template <class T>
class Mul{
	T _val;
public:
	Mul(const T & val):_val(val){}
	
	void operator () (T & elem) const {
		elem *= _val;
	}
};

class Apothecary{
public:
/*	vector<int> balance(int w){
		double ans = (double) w;
		vector<int> weights;
		double val = 1;
		double i = 0;
		do{
			val = pow(3.0,i);
			i++;	
			weights.push_back(val);
		}while(val < ans);
		vector<int> result;
		result.push_back(val);
		if(val == ans) return result;
		double lhs = (double)ans;
		double rhs = weights[weights.size()-1];
		weights.pop_back();
		vector<int> weights_for_left;
		vector<int> weights_for_right;
		int index_4_left = weights.size()-1;
		int _min = 1000000;
		int last_i ;
		do{
			int i;
			if(lhs < rhs){
				for(i = 0 ,_min = 1000000 , last_i = weights.size()-1; i < weights.size()  ; i++){
					val = weights[i];
					double r = lhs + val;
					double displacement =  abs(r - rhs);
					if( displacement < _min ){
						_min = displacement;
						last_i = i;
					}
				}
				i = last_i;
				val = weights[i];
				weights_for_left.push_back(val);
				weights.erase(weights.begin()+i);
				lhs += val;
			}else{
				for(i = 0 ,_min = 1000000 , last_i = weights.size()-1; i < weights.size()  ; i++){
					val = weights[i];
					double r = rhs + val;
					double displacement =  abs(r - lhs);
					if( displacement < _min ){
						_min = displacement;
						last_i = i;
					}
				}
				i = last_i;
				val = weights[i];
				weights_for_right.push_back(val);
				weights.erase(weights.begin()+i);
				rhs += val;
			}
		}while(lhs != rhs);
		for_each(weights_for_left.begin(),weights_for_left.end(),Mul<int>(-1));
		result.insert(result.end(),weights_for_left.begin(),weights_for_left.end());
		result.insert(result.end(),weights_for_right.begin(),weights_for_right.end());
		sort(result.begin(),result.end());
		return result;
	}*/

/*vector <int> balance(int W) {
    // !FDI
    vector<int> res;
    int qty = 1;
    while(W) {
      if(W % (qty*3) == 0) ;
      else if(W % (qty*3) == qty) {
        W -= qty;
        res.push_back(qty);
        }
      else {
        W += qty;
        res.push_back(-qty);
        }
      qty *= 3;
      }
    sort(res.begin(), res.end());
    return res;
    }*/
	vector<int> balance(int w){
		vector<int> r;
		int cur_wt = 1;
		while(w){
			if(w % 3 == 1){
				w -= 1;
				r.push_back(cur_wt);
			}
			else if(w % 3 == 2){
				w += 1;
				r.push_back(-cur_wt);
			}
			w /= 3;
			cur_wt *= 3;
		}
		sort(r.begin(),r.end());
		return r;
	}
};

int _tmain(int argc, _TCHAR* argv[]){

	int r[] = { -243,  -9,  81,  2187 };

	Apothecary a;
	int r1[] = { -9,  -1,  27 };
	are_equal<int>(to_vector<int,3>(r1),a.balance(17));
	are_equal<int>(to_vector<int,4>(r),a.balance(2016));
	
	int r2[] = { 1 };
	are_equal<int>(to_vector<int,1>(r2),a.balance(1));
	int r3[] = { -531441,  -59049,  -6561,  -243,  -27,  1,  81,  729,  2187,  1594323 };
	are_equal<int>(to_vector<int,10>(r2),a.balance(1000000));

	
	int ii;
	cin >> ii;
	return 0;
}