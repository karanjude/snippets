
binomial = [[0]*41]*41
solved = [-1]*41

def build_binomial():
    for i in range(0,41):
        binomial[i][i] = 1
        binomial[i][0] = 1
        for j in range(1,i):
            binomial[i][j] = binomial[i-1][j] + binomial[i-1][j-1]
    #print binomial

def solve(n,k,c):
    if solved[k] != -1:
        return solved[k]
    den = float(binomial[c-k][n])/float(binomial[c][n])
    factor = 1
    if (float(1.0) - den) > 0:
        factor = float(1.0)/(float(1.0) - den)
    ans = 0
    for j in range(1,min(n,k)+1):
        if k - j == 0:
            continue
        p = float(binomial[c-k][n-j] * binomial[k][j])/float(binomial[c][n])
        if p != 0:
            ans += p*solve(n,k-j,c)
    ans *= factor
    solved[k] = ans
    return ans
    
if __name__ == "__main__":
    build_binomial()
    c = 2
    n = 1
    k = c
    print solve(n,k,c)
    c = 3
    n = 2
    k = 3
    print solve(n,k,c)
