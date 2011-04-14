#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <map>
#include <cstdarg>

using namespace std;

class Term{
public:
  string op;
  bool marked;

protected:
  vector<Term*> children;

public:
  Term(const string& s):
    op(s)
  {
    marked = false;
  }

  string name(){
    return this->op;
  }

  void addChild(Term *term){
    children.push_back(term);
  }

  void safe_delete(){
    children.clear();
  }

  virtual string str () = 0;

  ~Term(){
      for(vector<Term*>::iterator i = children.begin(); i != children.end(); i++)
	if(*i != NULL)
	  delete *i;
  }
};


class Constant: public Term{
public:
  Constant(const string& op_):
    Term(op_)
  {
  }

  string str(){
    cout << endl << "Constant -> " << this->op;
    return "";
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
      for(vector<Term*>::iterator i = children.begin()+1; i != children.end(); i++){
	l->addChild(*i);
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
      l = new List("");
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
public:
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
    //s = replace(s.begin(), s.end(), ')', ' ) ");
    //s = replace(s.begin(), s.end(), "(", " ( ");
    i = 0;
    token_value = "";
    root = NULL;
  }

  ~Scanner(){
    delete root;
  }

  void skipwhite(){
    while(i < s.length() && s[i] == ' ')
      i++;
  }

  void token(){
    skipwhite();
    this->token_value = "";
    char c;
    while(i < s.length() and s[i] != ' '){
      c = s[i];
      token_value += c;
      i++;
      if(c == ')' || c == '(')
	break;
    }
  
    cout << endl << "token -> " << this->token_value;
  }

  bool match(string c){
    if(token_value == c)
      return true;
    return false;
  }

  bool match_operator(){
    return find(operators.begin(), operators.end(), token_value) != operators.end();
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
  for(vector<string>::iterator i=operators.begin(); i != operators.end(); i++)
    cout << endl << *i;
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

  static List* registerHandle(List* l){
    items.push_back(l);
    return l;
  }

  static void cleanup(){
    for(vector<Term*>::iterator i = items.begin(); i != items.end(); i++)
      if(instanceof<Term,Constant>(*i))
	delete *i;
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
    cout << endl << "adding : " << var->name() << "=" << x->name();
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
    return unify(Pool::registerHandle(xx->args()), Pool::registerHandle(yy->args()), 
		 unify(Pool::make_constant(x->op), Pool::make_constant(y->op), subs));
  }else if(instanceof<Term, List>(x) && instanceof<Term, List>(y)){
    List* xx = (List*) x;
    List* yy = (List*) y;
    return unify(Pool::registerHandle(xx->rest()), Pool::registerHandle(yy->rest()), unify(xx->first(), yy->first(), subs));
  }
  return NULL;
}
 
void store(vector<string>& r, const char* s, ...){
  va_list argptr;
  va_start(argptr, s);
  const char* ss = s;
  r.push_back(ss);
  while((ss = va_arg(argptr, const char* )) != 0)
    r.push_back(ss);
  va_end(argptr);
} 

void print_substitution(SubstitutionMap * subs){
  cout << endl << "size : " << subs->size();
  for(SubstitutionMap::iterator i = subs->begin(); i != subs->end(); i++){
    cout << endl << i->first <<  "/" << i->second;
  }
}

int main(int argc, char** argv){
  vector<string> variables, constants, lists, operators; 
  variables.push_back("x"); 
  variables.push_back("y"); 
  variables.push_back("a"); 
  variables.push_back("b"); 

  constants.push_back("10");
  constants.push_back("MyAge");

  operators.push_back("+");
  operators.push_back("<");
  operators.push_back("-");
  
  string s1 = "< ( x + ( y x ) )";
  string s2 = "< ( 10 + ( a b ) )";
  Scanner * scanner1 = new Scanner(s1, variables, constants, lists, operators);
  scanner1->expression(NULL);
  Term * e1 = scanner1->root;
  Scanner * scanner2 = new Scanner(s2, variables, constants, lists, operators);

  scanner2->expression(NULL);
  Term * e2 = scanner2->root;

  SubstitutionMap * subs = new SubstitutionMap;
  unify(e1, e2, subs);
  print_substitution(subs);

  delete subs;
  delete scanner1;
  delete scanner2;

  Pool::cleanup();



  return 0;
}
