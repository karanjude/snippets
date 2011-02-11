#include <cstdio>
#include <iostream>

using namespace std;

struct node{
  int value;
  node * left;
  node * right;

  node(int value_, node * left_ = NULL, node* right_ = NULL):
    value(value_),
    left(left_),
    right(right_){
  }

  void print(){
    if(left != NULL)
      left->print();
    cout << value;
    if(right != NULL)
      right->print();
  }

  node * clear(){
    if(NULL != left)
      left = left->clear();

    if(NULL != right)
      right = right->clear();

    if(NULL == left && NULL == right){
      cout << endl << "about to delete " << value;
      delete this;
      return NULL;
    }
  }
    
};

node* build_tree(int * tree_array, int start, int end, int length){
  int m = (start + end)/2;
  if( start > end || start < 0 || start >= length)
    return NULL;
  
  int i = m;
  if (i < 0 or i >= length)
      return NULL;

  node * root = 
      new node(tree_array[i], 
	    build_tree(tree_array, start, m - 1, length), 
	    build_tree(tree_array, m + 1, end, length));
  return root;
}
						     

int main(int argc, char** argv){
  int tree[] = {1,2,3,4,5};
  int length = sizeof(tree) / sizeof(int);
  node * n = build_tree(tree, 0, length, length);
  n->print();
  n->clear();
  return 0;
}
