import sys
import random

# 2068022353

def process_edge(v1,v2,exist,poly,n):
    if not exist[v1] or not exist[v2]:
        return
    if v1 > v2:
        v2 += n
    cnt = 0
    for i in range(v1+1,v2):
        if exist[i%n]:
            cnt += 1
    if cnt == 0:
        return
    v = [v1,v2%n]
    for j in range(v2-1,v1,-1):
        if exist[j%n]:
            v.append(j%n)
            exist[j%n] = False
    poly.append(v)

def free_color(p,c,g,v,color,vertex_to_poly_map, poly_color_map):
    #print "vertex : ", v
    #print vertex_to_poly_map , poly_color_map
    r = set([x for x in range(0,c)])
    colors = []
    #print poly_color_map
    for poly in vertex_to_poly_map[v]:
        l = [x for x in poly_color_map[poly] if x != -1]
        #print l
        if len(l) == 0:
            continue
        colors.append(set(l))
    #print colors
    if len(colors) > 0:
        r1 = colors[0]
        for rr in colors:
            r1 = r1.union(rr)
        r = r.difference(r1)
    #print "colors available :" , r
    r = list(r)
    if len(r) == 0:
        return -1
    return r[0]

def fill_room(p , color, c, g, vertex_to_poly_map, vertex_degree, poly_color_map):
    for v in vertex_degree:
        if color[v] == -1:
            x = free_color(p,c,g,v,color,vertex_to_poly_map, poly_color_map)
            if x == -1:
                continue
            color[v] = x
            for poly in vertex_to_poly_map[v]:
                poly_color_map[poly][color[v]] = color[v]

def process(n,m,u,v,g):
    #print n
    #print m
    #print u
    #print v
    edge = []
    poly = []
    for i in range(0,len(u)):
        a = u[i] - 1
        b = v[i] - 1
        d = (b-a+n)%n
        edge.append((d,[a,b]))
        d = (a-b+n)%n
        edge.append((d,[b,a]))
        edge.sort()
        exist = [True] * n
        #print edge
        #print exist
        for e in edge:
            v1 = e[1][0]
            v2 = e[1][1]
            process_edge(v1,v2,exist,poly,n)
    poly = sorted(poly, key=lambda x:len(x))
    #print poly
    c = len(poly[0])

    color = [-1] * n

    poly_hash = {}
    poly_set = []
    for p in poly:
        if poly_hash.has_key(tuple(p)):
            continue
        poly_hash[tuple(p)] = True
        poly_set.append(tuple(p))


    poly_hash = {}
    for pp in poly:
	for ppp in poly:
            if not poly_hash.has_key(tuple(pp)) and pp != ppp and set(pp).issuperset(set(ppp)):
                poly_hash[tuple(pp)] = True

    for p in poly_hash.keys():
        poly_set.remove(p)

    #print "polygons : " , poly_set

    vertex_to_poly_map = {}

    for p in range(0,len(poly_set)):
        for v in poly_set[p]:
            if vertex_to_poly_map.has_key(v) == False:
                vertex_to_poly_map[v] = []
            vertex_to_poly_map[v].append(p)

    #print "vertex poly map :", vertex_to_poly_map

    vertex_degree = []
    for v,p in vertex_to_poly_map.iteritems():
        vertex_degree.append((v,len(p)))

    vertex_degree = sorted(vertex_degree, key=lambda x:x[1], reverse = True)
    vertex_degree = map(lambda x: x[0], vertex_degree)

    #print "vertex degree map : ", vertex_degree
    
    poly_color_map = {}
    for p in range(0,len(poly_set)):
        poly_color_map[p] = [-1] * c

    for p in poly_set:
        fill_room(p,color,c,g,vertex_to_poly_map,vertex_degree, poly_color_map)
        
    print color
    for i in range(0,len(color)):
        if color[i] == -1:
            r1 = set([x for x in range(0,c)])
            r2 = []
            for n in g[i]:
                if color[n] != -1:
                    r2.append(color[n])
            r2 = set(r2)
            print r1 , r2
            r = r1.difference(r2)
            if len(r) == 0:
                color[i] = random.randint(0,c-1)
            else:
                color[i] = list(r)[0]
            print "vertex: ", i , "color : " , color[i]
            print vertex_to_poly_map
            for p in vertex_to_poly_map[i]:
                poly_color_map[p][color[i]] = color[i]
            print poly_color_map

    #print color
    print poly_color_map
    color = map(lambda x:random.randint(1,c) if x == -1 else x + 1,color)
    

    return (c, " ".join(map(str,color)))
        
        

if __name__ == "__main__":
    t = int(sys.stdin.readline().strip())
    for tt in range(0,t):
        n , m = sys.stdin.readline().strip().split()
        n , m = int(n) , int(m)
        u = map(int,sys.stdin.readline().strip().split())
        v = map(int,sys.stdin.readline().strip().split())
        g = {}
        for j in range(0,n):
            if g.has_key(j) == False:
                g[j] = []
            if g.has_key((j+1)%n) == False:
                g[(j+1)%n] = []
            if g.has_key((j-1+n)%n) == False:
                g[(j-1+n)%n] = []
            g[j].append((j+1)%n)
            g[(j+1)%n].append(j)
            g[j].append((j-1+n)%n)
            g[(j-1+n)%n].append(j)

        for i in range(0,len(u)):
            if g.has_key(u[i]-1) == False:
                g[u[i]-1] = []
            g[u[i]-1].append(v[i]-1)
            if g.has_key(v[i]-1) == False:
                g[v[i]-1] = []
            g[v[i]-1].append(u[i]-1)
         
        for k in g.keys():
            g[k] = list(set(g[k]))
        #print g

        a, b = process(n,m,u,v,g)
        print "Case #%s: %s" % (tt+1,a)
        print b









