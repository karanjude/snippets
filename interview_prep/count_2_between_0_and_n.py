def count_2(n):
    c = 0
    while n > 0:
        if n % 10 == 2:
            c += 1
        n = n / 10
    return c

def count_2s(n):
    c = 0
    for i in range(0,n+1):
        c += count_2(i)
    return c

print count_2s(1000)
