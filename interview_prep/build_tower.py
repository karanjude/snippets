'''
u are given a list of people with weight and height , u need to find the longest increasing subsequence 
given that u need to maintain an order such that person 2 has higher weight and height than person 1

'''


def mysort(x,y):
    if x[0] > y[0] and x[1] > y[1]:
        return 1
    elif x[0] == y[0] and x[1] == y[1]:
        return 0
    else:
        return -1


def process(seq):
    seq.sort(mysort)
    s = [1] * len(seq)
    v = [-1] * len(seq)

    
    for i in range(1,len(seq)):
        if seq[i][0] >= seq[i-1][0] and seq[i][1] >= seq[i-1][1]:
            s[i] += s[i-1]
            v[i] = i-1

    print v
    print "longest increasing sub sequence : " , s[len(seq)-1]
    i = len(seq) - 1
    print seq[i]
    while v[i] != -1:
        i = v[i]
        print seq[i]


if __name__ == "__main__":
    process([(65,100),(70, 150), (56, 90), (75, 190) ,(60, 95) ,(68,110)])
