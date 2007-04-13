#include "stdafx.h"

#include <vector>
#include <iostream>

using namespace std;


namespace my {
		template<class T , int SIZE>
		vector<T> to_vector(T source[]){
			vector<T> result;
			for(int i = 0 ; i < SIZE ; i++)	{
				result.push_back(source[i]);
			}
			return result;
		}

		template<class T>
		bool are_equal(vector<T> v1 , vector<T> v2){
			bool result = true;
			result = v1.size() == v2.size();
			for(int i = 0; i < v1.size(); i++){
				if(v1[i] != v2[i]) {
					result = false;
					break;
				}
			}

			print<T>(v1);
			print<T>(v2);
			cout << endl << "Equal : " << (result == true);

			return result;
		}

		template<class T>
		void are_equal_with_print(T expected , T result){
			cout << endl << endl << "[" << expected << " == " << result << " ] :";
			cout << ((expected == result ) ? " TRUE " : "FALSE");

		}

		template<class T>
		void print(vector<T> v){
			cout << endl;
			for(int i = 0; i < v.size() ; i++) {
				cout << "  " << v[i];
			}
		}

		template< class T , int SIZE , int Y> 
		void print_matrix( T (*matrix)[SIZE]) {
			cout << endl << endl;
			for(int i = 0; i < Y ; i++){
				cout << endl ;
				for(int j = 0; j < Y ; j++ ){
					cout << matrix[i][j];
				}
			}
		}

		template <class T>
		string to_string(T toBeConverted){
			ostringstream buffer;
			buffer << toBeConverted;
			return buffer.str();
		}

		static vector<string> split_string(string s , string ch){
			vector<string> result ;
			int j = 0;
			for(int i = 0;i < s.size();i = j + 1){
				j = s.find_first_of(ch,i);
				if(j == -1) j = s.size();
				if(j-i > 0 ) result.push_back(s.substr(i,(j-i))); 
			}
			return result;
		}

		template<class T , int SIZE>
		bool linear_search(T elements[] , T toFind){
			bool result = false;
			for(int i = 0;i < SIZE ; i++){
				if(elements[i] == toFind)
					return true;
			}
			return result;
		}

		template <class T,int SIZE>
		void selection_sort(T elements[]){
			for(int i = 0;i-1 < SIZE ; i++){
				int smallest_index = i;
				int smallest = 99999;
				for(int j = i;j < SIZE ; j++){
					if(elements[j] < smallest){
						smallest = elements[j];
						smallest_index = j;
					}
				}
				swap(elements[i],elements[smallest_index]);
			}
		}

		template<class T, int SIZE>
		T smallest_in(T elements[]){
			T result = elements[0];
			for(int i = 1;i < SIZE; i++){
				result = min(result,elements[i]);
			}
			return result;
		}
/*
		char* my_itoa(int number){
			char buffer[500];
			int n,r,i;
			n = r = i = 0;
			r = number % 10;
			while(r){
				buffer[i++] = '0' + r;
				number = number /10;
				r = number % 10;
			}while(r); 
			buffer[i] = NULL;
			char *result =  strrev(buffer);
			return result;
		}

		char * my_reverse(char * str){
			char * result = strdup(str);
			int n = strlen(str);
			for(int i = 0;i < n/2;i++){
				char x = result[i];
				result[i] = result[n-1-i];
				result[n-1-i] = x;
			}
			return result;
		}
		*/

		template < class T>
		void my_insert(vector<T> & v,int n){
			if(n > 0){
				if(v[n] < v[n-1])
					swap(v[n],v[n-1]);
				insert<T>(v,n-1);
			}
		}

		template < class T >
		void insertion_sort(vector<T> & v,int n){
			if(n > 0){
				insertion_sort<T>(v,n-1);
				my_insert<T>(v,n);
			}
		}

			template <class T>
		void merge(vector<T> & v,int p,int q,int r){
			vector<T> ll(v.begin()+p,v.begin()+q);
			vector<T> rr(v.begin()+q,v.begin()+r);
			int i,j;
			i = j = 0;
			for(int k = p;k < r;k++){
				if(i < ll.size() && j < rr.size() && ll[i] < rr[j])
					v[k] = ll[i++];
				else if(j < rr.size())
					v[k] = rr[j++];
				else
					v[k] = ll[i++];
			}
		}

		template < class T>
		void merge_sort(vector<T> & v,int p,int r){
			if(p < r){
				int q = (p+r)/2;
				merge_sort<T>(v,p,q);
				merge_sort<T>(v,q+1,r);
				merge<T>(v,p,q,r);
			}
		}

		

			template <class T>
		void binary_search(vector<T> & v,int p,int q,T a){
			int mid = (p+q)/2;
			int middle = v[mid];
			if(middle == a){
				cout << endl << "found";
				return;
			}
			if(p < q){
				if(a < middle){
					binary_search<T>(v,p,mid,a);
				}else{
					binary_search<T>(v,mid+1,q,a);
				}
			}
	}


}
