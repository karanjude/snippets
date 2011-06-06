import sys

def valid_pos(grid,rr,cc,r,c):
    if rr < r and cc < c:
        if grid[rr][cc] == '#':
            return True
        return False
    return False

def can_replace(grid,r,c,rr,cc):
    if valid_pos(grid,rr,cc,r,c) and valid_pos(grid,rr,cc+1,r,c) and valid_pos(grid,rr+1,cc,r,c) and valid_pos(grid,rr+1,cc+1,r,c):
        return True
    return False

def replace(grid,r,c,rr,cc):
    grid[rr][cc] = '/'
    grid[rr][cc+1] = '\\'
    grid[rr+1][cc] = '\\'
    grid[rr+1][cc+1] = '/'

def process(grid,r,c):
    for rr in range(0,r):
        for cc in range(0,c):
            if can_replace(grid,r,c,rr,cc):
                replace(grid,r,c,rr,cc)
    for rr in range(0,len(grid)):
        if "".join(grid[rr]).find('#') >= 0:
            return "Impossible"
        else:
            grid[rr] = "".join(grid[rr])
    return "\n".join(grid)

if __name__ == "__main__":
    n = int(sys.stdin.readline().strip())
    for i in range(0,n):
        print "Case #%i:" % (i+1) 
        r,c = sys.stdin.readline().strip().split()
        r = int(r)
        c = int(c)
        grid = [[]*c]*r
        for rr in range(0,r):
            grid[rr] = list(sys.stdin.readline().strip())
        print process(grid,r,c)
