
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
        return self.match('<') or self.match('+')

    def operator(self):
        self.token()
        self.match('(')
        self.expression()
        self.expression()
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
        return self.isvariable(self.token_value)

    def match_constant(self):
        return self.isconstant(self.token_value)

    def match_list_item(self):
        return self.match_variable() or self.match_constant()

    def listitem(self):
        if(self.match_list_item()):
            print "listitem->", self.token_value
            self.token()
            self.listitem()

    def list(self):
        print "list->", self.token_value
        self.token()
        self.match('(')
        self.token()
        self.listitem()
        self.match(')')

    def constant(self):
        print "constant->",self.token_value

    def variable(self):
        print "variable->",self.token_value

    def expression(self):
        self.token()
        if(self.match_opertor()):
            self.operator()
        elif(self.match_list()):
            self.list()
        elif(self.match_variable()):
            self.variable()
        elif(self.match_constant()):
            self.constant()
    

if __name__ == "__main__":
    '''
    s = "< ( x + ( y x ) )"
    variables = ["x","y","a","b"]
    constants = ["10"]
    lists = []
    operators = ["+","<"]
    scanner = Scanner(s, variables, constants, lists, operators)
    s = "< ( 10 + ( a b ) )"
    scanner = Scanner(s, variables, constants, lists, operators)
    scanner.expression()
    '''
    s = "< ( + ( V ( 1 2 3 ) Nums ( x x x )) + ( V ( 1 2 3 ) V ( 1 2 3 )))"
    variables = ["x","y"]
    constants = ["10","11","12","1","2","3"]
    lists = ["V","Nums"]
    operators = ["+","-","<"]
    scanner = Scanner(s, variables, constants, lists, operators)
    scanner.expression()
