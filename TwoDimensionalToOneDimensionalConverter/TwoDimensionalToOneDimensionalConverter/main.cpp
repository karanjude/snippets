#include <iostream>

using namespace std;


template<class T , int SIZE> 
T* Covert2DTo1DimensionalArray( T source[SIZE][SIZE] , int width , int height ){
	int length = width * height;
	T * _array = new T[length];
	int ctr = 0;
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width ; x++ ){
			_array[ctr++] = source[y][x];
		}
	}
	return _array;
}


/*int main(int argc, char * argv[]){

	int source[4][4] = {	
						{1,2,3,4},
						{4,5,6,4},
						{7,8,9,4},
						{1,2,3,4}
	};

	int * arr =  Covert2DTo1DimensionalArray<int,4>(source,4,4);
    for(int i = 0 ;i < 16;i++)
		cout << " " << arr[i];
	int i;
	cin >> i;
	return 0;
}
*/

