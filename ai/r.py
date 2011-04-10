
class Compound():
    def __init__(self, v):
        self.op = v
        self.children = []

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
            print str(c)
        return ""


class List():
    def __init__(self, v):
        self.op = v
        self.children = []

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
                str(c)
        return r

class Variable():
    def __init__(self, v):
        self.op = v

    def name(self):
        return self.op

    def __str__(self):
        print "Variable -> " , self.op , " "
        return ""

class Constant():
    def __init__(self, v):
        self.op = v

    def name(self):
        return self.op

    def __str__(self):
        print "Constant -> " , self.op , " "
        return ""

class Scanner():
    def __init__(self,s, variables, constants, lists, operators):
        self.i = 0
        self.s = s
        self.token_value = ""
        self.variables = variables
        self.constants = constants
        self.lists = lists
        self.operators = operators

    def skipwhite(self):
        while(self.i < len(self.s) and self.s[self.i] == ' '):
            self.i+=1

    def token(self):
        self.skipwhite()
        self.token_value = ""
        while(self.i < len(self.s) and self.s[self.i] != ' '):
            self.token_value += self.s[self.i]
            self.i += 1
            if(self.token_value == ')' or self.token_value == '('):
                break
        #print "token->",self.token_value    
            
    def match(self,c):
        if(self.token_value == c):
            if c in operators:
                print "operator->", c
            return True

    def match_opertor(self):
        r = False
        for op in self.operators:
            r = self.match(op)
            if(r):
                break
        return r

    def operator(self, parent):
        self.token()
        self.match('(')
        self.expression(parent)
        self.expression(parent)
        self.token()
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
        if(self.match_variable()):
            print "listitem->", self.token_value
            self.variable(parent)
            self.token()
            self.listitem(parent)

        elif(self.match_constant()):
            print "listitem->", self.token_value
            self.constant(parent)
            self.token()
            self.listitem(parent)


    def list(self, parent):
        print "list->", self.token_value
        l = List(self.token_value)
        self.token()
        self.match('(')
        self.token()
        self.listitem(l)
        self.match(')')
        if parent is None:
            self.root = l
        else:
            parent.addChild(l)

    def constant(self, parent):
        print "constant->",self.token_value
        if parent is None:
            self.root = Constant(self.token_value)
        else:
            parent.addChild(Constant(self.token_value))
            

    def variable(self, parent):
        print "variable->",self.token_value
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
        elif(self.match_list()):
            self.list(parent)
        elif(self.match_variable()):
            self.variable(parent)
        elif(self.match_constant()):
            self.constant(parent)

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
    print subs
    if( x is None or y is None):
        return subs
    elif(isinstance(x,Variable)):
        return unify_var(x,y, subs)
    elif(isinstance(y,Variable)):
        return unify_var(y,x, subs)
    elif(isinstance(x,Compound) and isinstance(y,Compound)):
        return unify(x.args(), y.args(), unify(x.op, y.op, subs))
    elif(isinstance(x,List) and isinstance(y,List)):
        return unify(x.rest(), y.rest(), unify(x.first(), y.first(), subs))
    elif(isinstance(x,str) and isinstance(y,str) and x == y):
        return subs
    return subs

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

    '''
    s = "< ( + ( V ( 1 2 3 ) Nums ( x x x )) + ( V ( 1 2 3 ) V ( 1 2 3 )))"
    variables = ["x","y"]
    constants = ["10","11","12","1","2","3"]
    lists = ["V","Nums"]
    operators = ["+","-","<"]
    scanner = Scanner(s, variables, constants, lists, operators)
    scanner.expression(None)
    '''

