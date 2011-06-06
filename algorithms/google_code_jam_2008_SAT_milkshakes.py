import sys

def process(flavors,customers):
    c = {}
    f = {}
    u = []
    m = []
    for i in range(1,flavors+1):
        f[i] = (0,None)
    for k,v in customers.iteritems():
        c[k] = 0
        for vv in v:
            if vv[1] == 1:
                m.append((k,vv[0]))
            else:
                u.append((k,vv[0]))
    possible = False
    while len(u) > 0 or len(m) > 0:
        ans = 1
        for k,v in c.iteritems():
            if v >= 1:
                ans &= 1
            else:
                ans &= 0
        if ans:
            possible = True
            break
        if len(u) > 0:
            v = u[0]
            del u[0]
            customer = v[0]
            flavor = v[1]
            if f[flavor][0] == 1:
                return "IMPOSSIBLE"
            if f[flavor][0] == 0:
                existing_customer = f[flavor][1]
                if existing_customer != None and c[existing_customer] > 1:
                    c[existing_customer] -= 1
                c[customer] += 1
                f[flavor] = (0,customer)
        if len(m) > 0:
            v = m[0]
            del m[0]
            customer = v[0]
            flavor = v[1]
            c[customer] += 1
            if f[flavor][1] != None:
                if f[flavor][0] == 0:
                    existing_customer = f[flavor][1]
                    c[existing_customer] -= 1
                    u.append((existing_customer,flavor))
            f[flavor] = (1,customer)
    if possible:
        return " ".join(map(lambda x:str(x[1][0]),f.iteritems()))
    return "IMPOSSIBLE"

if __name__ == "__main__":
    n = int(sys.stdin.readline().strip())
    for i in range(0,n):
        flavors = int(sys.stdin.readline().strip())
        customer_count = int(sys.stdin.readline().strip())
        customers = {}
        for c in range(0,customer_count):
            customer_line = sys.stdin.readline().strip()
            line = customer_line.split()
            ctr = 0
            if not customers.has_key(c):
                customers[c] = []
            for l in range(1,len(line),2):
                customers[c].append((int(line[l]),int(line[l+1])))
        print "Case #%i: %s" % (i+1,process(flavors,customers))
