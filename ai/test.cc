#include <iostream>
#include <stack>
#include <iterator>
#include <vector>

using namespace std;

template< typename container>
class A {
protected:
  container s;
public:
  
  A(){
    cout << endl << "A() created";
  }

  void print(){
    //       typedef typename container::value_type t ;
    typedef typename container::iterator iterator;
    for(iterator  i = s.begin(); i != s.end(); i++)
      cout << endl << *i;

  }


  ~A(){
    cout << endl << "~B() called";
  }

};

template<typename container>
class B : public A<container> {
public:
  B(){
    A<container>::s.push_back(1);
    cout << endl << "B() created";
  }

  ~B(){
    cout << endl << "~B() called";
  }
};

int main(){
  B< vector<int> > b;
  b.print();
}
