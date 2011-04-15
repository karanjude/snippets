#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <map>
#include <cstdarg>
#include <fstream>
#include <sstream>

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
    if(marked)
      children.clear();
    else
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
    return op;
  }
};

class Variable: public Term{
public:
  Variable(const string& op_):
    Term(op_){
  }


  string str(){
    return op;
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
    ostringstream ss;
    ss << "[";
    int c = 1;
    for(vector<Term*>::iterator i = children.begin(); i != children.end(); i++, c++){
      if(c > 1)
	ss << ", ";
      ss << (*i)->str();
    }
    ss << "]";
    return ss.str();
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
    ostringstream ss;
    ss << op << "(";
    int c = 1;
    for(vector<Term*>::iterator i = children.begin(); i != children.end(); i++, c++){
      if(c > 1)
	ss << ", ";
      ss << (*i)->str();
    }
    ss << ")";
    return ss.str();
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
  
    //cout << endl << "token -> " << this->token_value;
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
  // cout << endl << "list ->" << token_value;
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
  if(NULL == x)
    return false;
  //cout << endl << "name : " << x->name();
  A* v = dynamic_cast<A*>(x);
  return v != 0;
}

typedef map<string, string> SubstitutionMap;

bool has_key(SubstitutionMap* subs, const string& key){
  return subs->find(key) != subs->end();
}

class Pool {
private:
  vector<Term*> items;
public:
  Constant* make_constant(const string& s){
    Constant * c = new Constant(s);
    items.push_back(c);
    return c;
  }

  List* registerHandle(List* l){
    if(NULL != l){
      l->marked = true;
      items.push_back(l);
    }
    return l;
  }

  ~Pool(){
    for(vector<Term*>::iterator i = items.begin(); i != items.end(); i++)
	delete *i;
  }
};

//vector<Term*> Pool::items;

SubstitutionMap* unify(Term* , Term* , SubstitutionMap* , Pool *);

string print_term(ostringstream& ss, Term * term){
  ss << "[";
  if(NULL != term){
    ss << term->str();
  }else{
    ss << "[]";
  }
  ss << "]";
  return ss.str();
}

string print_term1(ostringstream& ss, Term * term){
  if(NULL != term){
    ss << term->str();
  }else{
    ss << "[]";
  }
  return ss.str();
}

void print_substitution(ostringstream& ss, SubstitutionMap * subs){
  if(NULL == subs)
    return;
  ss << "{";
  int c = 1;
  for(SubstitutionMap::iterator i = subs->begin(); i != subs->end(); i++, c++){
    if(c > 1)
      ss << ", ";
    ss << i->first <<  "/" << i->second;
  }
  ss << "}";
}


void print_substitution(SubstitutionMap * subs){
  //cout << endl << "size : " << subs->size();
  for(SubstitutionMap::iterator i = subs->begin(); i != subs->end(); i++){
    cout << endl << i->first <<  "/" << i->second;
  }
}

void print_unify(Term* x, Term *y, SubstitutionMap* subs){
  ostringstream ss;
  ss << "Unify(";
  print_term(ss, x);
  ss << ", ";
  print_term(ss, y);
  ss << ", ";
  print_substitution(ss, subs);
  ss << ")";
  cout << ss.str() << endl;
}

void print_unify_var(Term* x, Term *y, SubstitutionMap* subs){
  ostringstream ss;
  ss << "Unify-Var(";
  print_term(ss, x);
  ss << ", ";
  print_term(ss, y);
  ss << ", ";
  print_substitution(ss, subs);
  ss << ")";
  cout << "\t" << ss.str() << endl;
}

SubstitutionMap* unify_var(Term* var, Term* x, SubstitutionMap* subs, Pool* pool){
  string val = "";
  print_unify_var(var, x, subs);
  if(instanceof<Term, Variable>(var) && has_key(subs, var->name())){
    val = (*subs)[var->name()];
    return unify(pool->make_constant(val), x, subs, pool);
  }else if(instanceof<Term, Variable>(x) && has_key(subs, x->name())){
    val = (*subs)[x->name()];
    return unify(var, pool->make_constant(val), subs, pool);
  }else{
    //cout << endl << "adding : " << var->name() << "=" << x->name();
    (*subs)[var->name()] = x->name();
  }
  return subs;
}

bool failure = false;


SubstitutionMap* unify(Term *x, Term* y, SubstitutionMap* subs, Pool* pool){
  print_unify(x, y, subs);
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
    return unify_var(x,y, subs, pool);
  }else if(instanceof<Term, Variable>(y)){
    return unify_var(y, x, subs, pool);
  }else if(instanceof<Term, Compound>(x) && instanceof<Term, Compound>(y)){
    Compound* xx = (Compound*) x;
    Compound* yy = (Compound*) y;
    return unify(pool->registerHandle(xx->args()), pool->registerHandle(yy->args()), 
		 unify(pool->make_constant(x->op), pool->make_constant(y->op), subs, pool), pool);
  }else if(instanceof<Term, List>(x) && instanceof<Term, List>(y)){
    List* xx = (List*) x;
    List* yy = (List*) y;
    return unify(pool->registerHandle(xx->rest()), 
		 pool->registerHandle(yy->rest()), unify(xx->first(), yy->first(), subs, pool), pool);
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

string lhs, rhs;

SubstitutionMap * solve_expression(const string& s1, const string& s2,
		      vector<string>& variables,
		      vector<string>& constants,
		      vector<string>& lists,
		      vector<string>& operators){

  Scanner * scanner1 = new Scanner(s1, variables, constants, lists, operators);
  scanner1->expression(NULL);
  Term * e1 = scanner1->root;
  Scanner * scanner2 = new Scanner(s2, variables, constants, lists, operators);

  scanner2->expression(NULL);
  Term * e2 = scanner2->root;

  SubstitutionMap * subs = new SubstitutionMap;
  Pool * pool = new Pool();
  
  unify(e1, e2, subs, pool);
  ostringstream ssl, ssr;
  print_term1(ssl, e1);
  lhs = ssl.str();
  print_term1(ssr, e2);
  rhs = ssr.str();

  //print_substitution(subs);

  delete scanner1;
  delete scanner2;
  delete pool;

  return subs;
}

/*int main(int argc, char** argv){
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
  solve_expression(s1, s2, variables, constants, lists, operators);

  return 0;
  }*/

bool trace = false;
bool noOccurCheck = false;
string file_name = "";
enum input_type {OPERATORS, VARIABLES, CONSTANTS, LISTS, LHS, RHS};
vector<string> variables, constants, lists, operators;


void process_line(const string& line, input_type data_type){
  switch(data_type){
  case OPERATORS:
    operators.push_back(line);
    break;
  case VARIABLES:
    variables.push_back(line);
    break;
  case CONSTANTS:
    constants.push_back(line);
    break;
  case LISTS:
    lists.push_back(line);
    break;
  case LHS:
    lhs += " " + line;
    break;
  case RHS:
    rhs += " " + line;
    break;
  }
}

template<typename T>
void print_vector(vector<T>& v, const string& label){
  cout << endl << label;
  for(typename vector<T>::iterator i = v.begin(); i!= v.end(); i++)
    cout << " " << *i; 
}

void dump_information(){
  print_vector(variables, "variables");
  print_vector(operators, "operators");
  print_vector(constants, "constants");
  print_vector(lists, "lists");
  cout << endl << "LHS:" << lhs;
  cout << endl << "RHS:" << rhs;
}


int main(int argc, char** argv){
  string file_name;
  if(argc > 1){
    int i = 1;
    while(i < argc){
      string option = argv[i];
      if("-noOccurCheck" == option)
	noOccurCheck = true;
      else if("-trace" == option)
	trace = true;
      else
	file_name = option;

      i++;
    }
  }

  if(file_name.length() == 0){
    cerr << endl << "no file provided, please provide file";
    return -1;
  }

  ifstream file(file_name.c_str());
  if(!file.good()){
    cerr << endl << "Error opening file :" << file_name;
    return -1;
  }

  input_type data_type;

  string line;
  while(!file.eof()){
    line = "";
    file >> line;
    
    //cout << endl << line;

    if("@OPERATORS:" == line){
      data_type = OPERATORS;
      continue;
    }
    else if("@VARIABLES:" == line){
      data_type = VARIABLES;
      continue;
    }
    else if("@CONSTANTS:" == line){
      data_type = CONSTANTS;
      continue;
    }
    else if("@LISTS:" == line){
      data_type = LISTS;
      continue;
    }
    else if("@LHS:" == line){
      data_type = LHS;
      continue;
    }
    else if("@RHS:" == line){
      data_type = RHS;
      continue;
    }
    if(line.length() > 0)
      process_line(line, data_type);
  }

  file.close();

  //dump_information();

  SubstitutionMap *subs = solve_expression(lhs, rhs, variables, constants, lists, operators);
  cout << "LHS: " << lhs;
  cout << endl << "RHS: " << rhs;

  ostringstream ss;
  print_substitution(ss , subs);

  cout << endl << "Substitution: " << ss.str() << endl;
  return 0;
}
