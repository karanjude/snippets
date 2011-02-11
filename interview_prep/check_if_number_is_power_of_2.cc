#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char ** argv){
  string input;
  if(argc > 1)
    input = argv[1];
  
  int i;

  stringstream ss(input);
  ss >> i;
  

  // the reason this works is becasue of the fact a number that is power of two will have only 1 bit set
  // and it can be thought that number is derived by adding 1 bit to number -1 , so anding number and 
  // number -1 will obviously be 0 and its ! would be 1 
  bool is_power_of_two = 0 != i && !(i  &(i-1));
  if(is_power_of_two)
    cout << endl << "True";
  else
    cout << endl << "False";

  return 0;
}
