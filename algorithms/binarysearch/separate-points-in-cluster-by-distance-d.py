import sys
'''
imaging u have a cluster of points distributed at various points. So u have 2 or more points at 1 point. Now
u want to separate these points by a distance 'd' and then measure the time taken 't' to do so. 

Now if u want to do this , u can create a range of time intervals and use a binary search to narrow 
down the choices to a fine interval. the final result then is the point that refers to the time 
when all points can be separated by a distance 'd'
'''


MAXV = float(10000000000000)

def is_valid(t,d,points):
    min_score = -MAXV
    for i in range(0,len(points)):
        next = max(min_score + d,points[i] - t)
        if(next > points[i] + t):
            return False
        min_score = next
    return True

def process(n,d,points):
    l = 0
    h = MAXV
    for i in range(0,100):
        mid = float(h+l)/float(2)
        if(is_valid(mid,d,points)):
            h = mid
        else:
            l = mid
    return h

if __name__ == "__main__":
    t = (sys.stdin.readline().strip())
    for tt in range(0,int(t)):
        n,d = (sys.stdin.readline().strip().split())
        points = []
        for l in range(0,int(n)):
            point_no,num_of_points = sys.stdin.readline().strip().split()
            for j in range(0,int(num_of_points)):
                points.append(int(point_no))
        print "Case #%s: %s" % (tt+1,process(int(n),int(d),points))
        
