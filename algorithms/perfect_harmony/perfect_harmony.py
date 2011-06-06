import sys

def gcd(num1, num2):
    if num1 > num2:
        for i in range(1,num2+1):
            if num2 % i == 0:
                if num1 % i == 0:
                    result = i
        return result

    elif num2 > num1:
        for i in range(1,num1+1):
            if num1 % i == 0:
                if num2 % i == 0:
                    result = i
        return result

    else:
        result = num1*num2/num1
        return result

def lcm(num1, num2):
    result = num1*num2/gcd(num1,num2)
    return result


class MyXRange(object):
    def __init__(self, a1, a2=None, step=1):
        if step == 0:
            raise ValueError("arg 3 must not be 0")
        if a2 is None:
            a1, a2 = 0, a1
        if (a2 - a1) % step != 0:
            a2 += step - (a2 - a1) % step
        if cmp(a1, a2) != cmp(0, step):
            a2 = a1
        self.start, self.stop, self.step = a1, a2, step

    def __iter__(self):
        n = self.start
        while cmp(n, self.stop) == cmp(0, self.step):
            yield n
            n += self.step

    def __repr__(self):
        return "MyXRange(%d,%d,%d)" % (self.start, self.stop, self.step)

    # NB: len(self) will convert this to an int, and may fail
    def __len__(self):
        return (self.stop - self.start)//(self.step)

    def __getitem__(self, key):
        if key < 0:
            key = self.__len__() + key
            if key < 0:
                raise IndexError("list index out of range")
            return self[key]
        n = self.start + self.step*key
        if cmp(n, self.stop) != cmp(0, self.step):
            raise IndexError("list index out of range")
        return n

    def __reversed__(self):
        return MyXRange(self.stop-self.step, self.start-self.step, -self.step)

    def __contains__(self, val):
        if val == self.start: return cmp(0, self.step) == cmp(self.start, self.stop)
        if cmp(self.start, val) != cmp(0, self.step): return False
        if cmp(val, self.stop) != cmp(0, self.step): return False
        return (val - self.start) % self.step == 0


def process(l,h,num):
    found = False
    for n in MyXRange(l,h+1):
        ctr = 0
        for nn in num:
            if nn % n == 0 or n % nn == 0:
                ctr += 1
            else:
                break
        if ctr == len(num):
            return n
        
    if not found:
        return "NO"

if __name__ == "__main__":
    t = int(sys.stdin.readline().strip())
    for tt in range(0,t):
        n,l,h = sys.stdin.readline().strip().split()
        l = int(l)
        h = int(h)
        num = map(int,sys.stdin.readline().strip().split())
        print "Case #%i: %s" %  (tt+1,process(l,h,num))

    
