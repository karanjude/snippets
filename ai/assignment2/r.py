debug = False


class Compound():
    def __init__(self, v):
        self.op = v
        self.children = []
        self.prefix = ""

    def addChild(self, c):
        self.children.append(c)

    def args(self):
        if len(self.children) > 0:
            l = List("")
            for c in self.children:
                l.addChild(c)
        else:
            l = None
        return l

    def __str__(self):
        print "Compound -> " , self.op , " "
        for c in self.children:
            c.prefix = self.prefix + "\t"
            print self.prefix, str(c)
        return ""


class List():
    def __init__(self, v):
        self.op = 
        self.children = []
        self.prefix = ""

    def addChild(self, c):
        self.children.append(c)

    def first(self):
        c = None
        if len(self.children) > 0:
            c = self.children[0]
        return c

    def rest(self):
        l = None
        if len(self.children) > 1:
            l = List("")
            for c in self.children[1:]:
                l.addChild(c)
        return l

    def __str__(self):
        r = ""
        print "List -> " , self.op , " "
        for c in self.children:
            if c is not None:
                c.prefix = self.prefix + "\t"
                print self.prefix, str(c)
        return r

class Variable():
    def __init__(self, v):
        self.op = v
        self.prefix = ""

    def name(self):
        return self.op

    def __str__(self):
        print self.prefix, "Variable -> " , self.op , " "
        return ""

class Constant():
    def __init__(self, v):
        self.op = v
        self.prefix = ""

    def name(self):
        return self.op

    def __str__(self):
        print self.prefix, "Constant -> " , self.op , " "
        return ""

class Scanner():
    def __init__(self,s, variables, constants, lists, operators):
        self.i = 0
        self.s = s.replace(")"," )")
        self.token_value = ""
        self.variables = variables
        self.constants = constants
        self.lists = lists
        self.operators = operators

    def skipwhite(self):
        while(self.i < len(self.s) and self.s[self.i] == ' '):
            self.i+=1

    def token(self, alnum = False):
        self.skipwhite()
        self.token_value = ""
        while(self.i < len(self.s) and self.s[self.i] != ' '):
            v = self.s[self.i]
            self.token_value += v
            self.i += 1
            if(v == ')' or v == '('):
                break


        print "token->",self.token_value    
            
    def match(self,c):
        if(self.token_value == c):
            #if c in operators:
            #    print "operator->", c
            return True

    def match_opertor(self):
        r = False
        for op in self.operators:
            r = self.match(op)
            if(r):
                break
        return r

    def doexpression(self, parent):
        r = self.expression(parent)
        if(r):
            self.doexpression(parent)

    def operator(self, parent):
        self.token()
        self.match('(')
        self.doexpression(parent)
        #self.expression(parent)
        #self.token()
        self.match(')')

    def islist(self, v):
        return v in self.lists

    def isvariable(self, v):
        return v in self.variables

    def isconstant(self, v):
        return v in self.constants

    def match_list(self):
        return self.islist(self.token_value)

    def match_variable(self):
        r = self.isvariable(self.token_value)
        return r

    def match_constant(self):
        r = self.isconstant(self.token_value)
        return r

    def listitem(self, parent):
        if(self.match_opertor()):
            #print "listitem->", self.token_value
            c = Compound(self.token_value)
            self.operator(c)
            if parent is None:
                self.root = c
            else:
                parent.addChild(c)
            self.token(True)
            self.listitem(parent)
        elif(self.match_list()):
            #print "listitem->", self.token_value
            self.list(parent)
            self.token(True)
            self.listitem(parent)
        elif(self.match_variable()):
            #print "listitem->", self.token_value
            self.variable(parent)
            self.token(True)
            self.listitem(parent)
        elif(self.match_constant()):
            #print "listitem->", self.token_value
            self.constant(parent)
            self.token(True)
            self.listitem(parent)

    def list(self, parent):
        print "list->", self.token_value
        l = List(self.token_value)
        self.token()
        self.match('(')
        self.token(True)
        self.listitem(l)
        self.match(')')
        if parent is None:
            self.root = l
        else:
            parent.addChild(l)

    def constant(self, parent):
        #print "constant->",self.token_value
        if parent is None:
            self.root = Constant(self.token_value)
        else:
            parent.addChild(Constant(self.token_value))
            

    def variable(self, parent):
        #print "variable->",self.token_value
        if parent is None:
            self.root = Variable(self.token_value)
        else:
            parent.addChild(Variable(self.token_value))

    def expression(self, parent):
        self.token()
        if(self.match_opertor()):
            c = Compound(self.token_value)
            self.operator(c)
            if parent is None:
                self.root = c
            else:
                parent.addChild(c)
            return True
        elif(self.match_list()):
            self.list(parent)
            return True
        elif(self.match_variable()):
            self.variable(parent)
            return True
        elif(self.match_constant()):
            self.constant(parent)
            return True
        else:
            return False

def unify_var(var,x, subs):
    if((isinstance(var, Variable)) and subs.has_key(var.name()) ):
        val = subs[var.name()]
        return unify(Constant(val), x, subs)
    elif((isinstance(x, Variable)) and subs.has_key(x.name())):
        val = subs[x.name()]
        return unify(var, Constant(val), subs)
    else:
        subs[var.name()] = x.name()
    return subs
               
   
def unify(x,y, subs):
    if( subs is None):
        print "Failure"
    if( x is None or y is None):
        return subs
    if(isinstance(x,str) and isinstance(y,str) and x == y):
        return subs
    if(isinstance(x,Constant) and isinstance(y,Constant) and x.op == y.op):
        return subs
    elif(isinstance(x,Variable)):
        return unify_var(x,y, subs)
    elif(isinstance(y,Variable)):
        return unify_var(y,x, subs)
    elif(isinstance(x,Compound) and isinstance(y,Compound)):
        return unify(x.args(), y.args(), unify(x.op, y.op, subs))
    elif(isinstance(x,List) and isinstance(y,List)):
        return unify(x.rest(), y.rest(), unify(x.first(), y.first(), subs))
    else:
        return None

if __name__ == "__main__":
    variables = ["x","y","a","b"]
    constants = ["10","MyAge"]
    lists = []
    operators = ["+","<","-"]
    s1 = "< ( x + ( y x ) )"
    s2 = "< ( 10 + ( a b ) )"
    scanner = Scanner(s1, variables, constants, lists, operators)
    scanner.expression(None)
    e1 = scanner.root
    #print "E1->", e1
    scanner = Scanner(s2, variables, constants, lists, operators)
    scanner.expression(None)
    e2 = scanner.root
    #print "E2->", e2

    subs = {}
    subs = unify(e1, e2, subs )
    print subs

    variables = ["x","y"]
    constants = ["10","11","12"]
    lists = ["V","Nums"]
    operators = ["+","-"]
    s1 = "V ( x y x)"
    s2 = "Nums ( 10 11 12) "
    scanner = Scanner(s1, variables, constants, lists, operators)
    scanner.expression(None)
    e1 = scanner.root
    #print "E1->", e1
    scanner = Scanner(s2, variables, constants, lists, operators)
    scanner.expression(None)
    e2 = scanner.root
    #print "E2->", e2

    subs = {}
    subs = unify(e1, e2, subs )
    print subs

    variables = ["a","b","c"]
    constants = ["1","2","3"]
    lists = ["L1","L2"]
    operators = []
    s1 = "L1 ( a 2 c )"
    s2 = "L2 ( 1 b 3 ) "
    scanner = Scanner(s1, variables, constants, lists, operators)
    scanner.expression(None)
    e1 = scanner.root
    #print "E1->", e1
    scanner = Scanner(s2, variables, constants, lists, operators)
    scanner.expression(None)
    e2 = scanner.root
    #print "E2->", e2

    subs = {}
    subs = unify(e1, e2, subs )
    print subs

    variables = ["x","y","z","a","b","c"]
    constants = ["age","1","2","3","4","5","10"]
    lists = ["L1","L2","L3","L4"]
    operators = ["plus","minus","<"]
    s1 = "plus ( L1 ( x y L2 ( a b c ) ) age )"
    s2 = "plus ( L3 ( 1 2 L4 ( 1 2 3 ) ) z ) "
    scanner = Scanner(s1, variables, constants, lists, operators)
    scanner.expression(None)
    e1 = scanner.root
    #print "E1->", e1
    scanner = Scanner(s2, variables, constants, lists, operators)
    scanner.expression(None)
    e2 = scanner.root
    #print "E2->", e2

    subs = {}
    subs = unify(e1, e2, subs )
    print subs

    variables = ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"]
    constants = ["0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","age","height","weight"]
    lists = ["L1","L2","L3","L4","L5","L6"]
    operators = ["+","-","/","*","avg","favorite","max"]
    s1 = "favorite ( L1 ( + ( 1 b ) - ( c max ( d 4 ) ) avg ( L2 ( f 6 h ) i 9 k ) L3 ( l B C ) ) )"
    s2 = "favorite ( L4 ( + ( a 2 ) - ( D max ( 3 e ) ) avg ( L5 ( 5 6 7 ) 8 j 0 ) L6 ( A B C ) ) )"
    scanner = Scanner(s1, variables, constants, lists, operators)
    scanner.expression(None)
    e1 = scanner.root
    e1.prefix = "\t"
    print "E1->", e1
    scanner = Scanner(s2, variables, constants, lists, operators)
    scanner.expression(None)
    e2 = scanner.root
    #print "E2->", e2

    subs = {}
    subs = unify(e1, e2, subs )
    print subs
    

    '''
    s = "< ( + ( V ( 1 2 3 ) Nums ( x x x )) + ( V ( 1 2 3 ) V ( 1 2 3 )))"
    variables = ["x","y"]
    constants = ["10","11","12","1","2","3"]
    lists = ["V","Nums"]
    operators = ["+","-","<"]
    scanner = Scanner(s, variables, constants, lists, operators)
    scanner.expression(None)
    '''

