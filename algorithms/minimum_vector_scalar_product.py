import sys

def process(l,r):
	ans = 0
        l.sort()
        r.sort(reverse = True)
        for i in range(0,len(l)):
            ans += l[i] * r[i]
	return ans

if __name__ == "__main__":
    f = sys.stdin
    n = int(f.readline().strip())
    for i in range(0,n):
        items = int(f.readline().strip())
        l = f.readline().strip()
        l = l.split()
        l = map(int,l)
        r = f.readline().strip()
        r = r.split()
        r = map(int,r)
        print "Case #%i: %i" % (i+1,process(l,r))

    
