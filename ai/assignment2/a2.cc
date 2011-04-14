#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

class Term{
public:
  string op;

protected:
  vector<Term*> children;

public:
  Term(const string& s):
    op(s)
  {
  }

  string name(){
    return this->op;
  }

  void addChild(Term *term){
    children.push_back(term);
  }

  virtual string str () = 0;
};


class Constant: public Term{
public:
  Constant(const string& op_):
    Term(op_)
  {
  }

  string str(){
    cout << endl << "Constant -> " << this->op;
    return this->op;
  }
};

class Variable: public Term{
public:
  Variable(const string& op_):
    Term(op_){
  }


  string str(){
    cout << endl << "Variable -> ", this->op;
    return "";
  }
};

class List: public Term {
public:
  List(const string& s):
    Term(s)
  {
  }

  Term* first(){
    Term * c = NULL;
    if(children.size() > 0){
      c = children[0];
    }
    return c;
  }
	       
  List* rest(){
    List* l = NULL;
    if(children.size() > 1){
      l = new List("");
      for(int i = 1; i <= children.size(); i++){
	l->addChild(children[i]);
      }
    }
    return l;
  }

  string str(){
    cout << endl << "List -> " << this->op;
      for(vector<Term*>::iterator i = children.begin(); i != children.end(); i++){
	cout << endl << (*i)->str();
      }
      return "";
  }

};


class Compound: public Term{
public:
  Compound(const string& op_):
    Term(op_)
  {
  }

  List* args(){
    List * l = NULL;
    if(children.size() > 0){
      List * l = new List("");
      for(vector<Term*>::iterator i = children.begin(); i != children.end(); i++){
	l->addChild(*i);
      }
    }
    return l;
  }

  string str(){
    cout << endl << "Compount -> " << this->op;
      for(vector<Term*>::iterator i = children.begin(); i != children.end(); i++){
	cout << endl << (*i)->str();
      }
      return "";
  }

};

class Scanner {
private:
  string s;
  vector<string> variables;
  vector<string> constants;
  vector<string> lists;
  vector<string> operators;
  int i;
  string token_value;
  Term * root;

public:
  Scanner(const string& s_, vector<string>& variables_, vector<string>& constants_,
	  vector<string>& lists_, vector<string>& operators_):
    s(s_),
    variables(variables_),
    constants(constants_),
    lists(lists_),
    operators(operators_)
  {
    s = s.replace(s.begin(), s.end(), ")", " ) ");
    s = s.replace(s.begin(), s.end(), "(", " ( ");
    i = 0;
    token_value = "";
    root = NULL;
  }

  void skipwhite(){
    while(i < s.length() && s[i] == ' ')
      i++;
  }

  void token(){
    skipwhite();
    token_value = "";
    char c;
    while(i < s.length() and s[i] != ' '){
      c = s[i];
      token_value += c;
      i++;
      if(c == ')' || c == '(')
	break;
    }
  
    cout << endl << "token -> " << token_value;
  }

  bool match(string c){
    if(token_value == c)
      return true;
    return false;
  }

  bool match_operator(){
    bool r = false;
    for(vector<string>::iterator i = operators.begin(); i != operators.end(); i++){
      r = match(*i);
      if(r)
	break;
    }
    return r;
  }

  bool expression(Term * parent);

  void doexpression(Term * parent){
    bool r = expression(parent);
    if(r)
      doexpression(parent);
  }

  void operate(Term* parent){
    token();
    match("(");
    doexpression(parent);
    match(")");
  }

  bool islist(const string& v){
    return find(lists.begin(), lists.end(), v) != lists.end();
  }

  bool isvariable(const string& v){
    return find(variables.begin(), variables.end(), v) != variables.end();
  }

  bool isconstant(const string& v){
    return find(constants.begin(), constants.end(), v) != constants.end();
  }

  bool match_list(){
    return islist(token_value);
  }

  bool match_variable(){
    return isvariable(token_value);
  }

  bool match_constant(){
    return isconstant(token_value);
  }
  
  void list(Term *);
  void variable(Term *parent){
    if(NULL == parent){
    }else{
      Variable * c = new Variable(token_value);
      parent->addChild(c);
    }
  }

  void constant(Term *parent){
    if(NULL == parent){
    }else{
      Constant * c = new Constant(token_value);
      parent->addChild(c);
    }
  }

  void listitem(Term* parent){
    if(match_operator()){
      Term * c = new Compound(token_value);
      operate(c);
      if( NULL == parent)
	root = c;
      else
	parent->addChild(c);
      token();
      listitem(parent);
    }else if(match_list()){
      list(parent);
      token();
      listitem(parent);
    }else if(match_variable()){
      variable(parent);
      token();
      listitem(parent);
    }else if(match_constant()){
      constant(parent);
      token();
      listitem(parent);
    }
  }


  
};

bool Scanner::expression(Term* parent){
  token();
  if(match_operator()){
    Compound * c = new Compound(token_value);
    operate(c);
    if(NULL == parent)
      root = c;
    else
      parent->addChild(c);
    return true;
  }else if(match_list()){
    list(parent);
    return true;
  }else if(match_variable()){
    variable(parent);
    return true;
  }else if(match_constant()){
    constant(parent);
    return true;
  }
  return false;
}

void Scanner::list(Term * parent){
    cout << endl << "list ->" << token_value;
    List* l = new List(token_value);
    token();
    match("(");
    token();
    listitem(l);
    match(")");
    if(NULL == parent)
      root = l;
    else
      parent->addChild(l);
  }

template<class B, class A>
bool instanceof(B * x){
  A* v = dynamic_cast<A*>(x);
  return v != 0;
}

typedef map<string, string> SubstitutionMap;

bool has_key(SubstitutionMap* subs, const string& key){
  return subs->find(key) != subs->end();
}


SubstitutionMap* unify(Term* , Term* , SubstitutionMap* );

class Pool {
private:
  static vector<Term*> items;
public:
  static Constant* make_constant(const string& s){
    Constant * c = new Constant(s);
    items.push_back(c);
    return c;
  }
};

vector<Term*> Pool::items;


SubstitutionMap* unify_var(Term* var, Term* x, SubstitutionMap* subs){
  string val = "";
  if(instanceof<Term, Variable>(var) && has_key(subs, var->name())){
    val = (*subs)[var->name()];
    return unify(Pool::make_constant(val), x, subs);
  }else if(instanceof<Term, Variable>(x) && has_key(subs, x->name())){
    val = (*subs)[x->name()];
    return unify(var, Pool::make_constant(val), subs);
  }else{
    (*subs)[var->name()] = x->name();
  }
  return subs;
}

bool failure = false;

SubstitutionMap* unify(Term *x, Term* y, SubstitutionMap* subs){
  if(failure)
    return NULL;
  else if(NULL == subs){
    cout << endl << "Failure";
    failure = true;
  }else if(NULL == x || NULL == y)
    return subs;
  else if(instanceof<Term,Constant>(x) && instanceof<Term,Constant>(y) && x->op == y->op){
    return subs;
  }else if(instanceof<Term, Constant>(x) && instanceof<Term,Constant>(y) and x->op == y->op){
    return subs;
  }else if(instanceof<Term, Variable>(x)){
    return unify_var(x,y, subs);
  }else if(instanceof<Term, Variable>(y)){
    return unify_var(y, x, subs);
  }else if(instanceof<Term, Compound>(x) && instanceof<Term, Compound>(y)){
    Compound* xx = (Compound*) x;
    Compound* yy = (Compound*) y;
    return unify(xx->args(), yy->args(), unify(Pool::make_constant(x->op), Pool::make_constant(y->op), subs));
  }else if(instanceof<Term, List>(x) && instanceof<Term, List>(y)){
    List* xx = (List*) x;
    List* yy = (List*) y;
    return unify(xx->rest(), yy->rest(), unify(xx->first(), yy->first(), subs));
  }
  return NULL;
}
 

int main(int argc, char** argv){
  return 0;
}
