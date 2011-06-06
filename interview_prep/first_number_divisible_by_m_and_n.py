import math

def is_prime(n):
    for i in range(2,n/2):
        if n % i == 0:
            return False
    return True

def primes(n):
    for i in range(2,n+1):
        if is_prime(i):
            yield i

def primes_less_than(m,n):
    for p in primes(m+n+1):
        yield p

def r_disivible_by_both(m,n):
    q = 1
    for p in primes_less_than(m,n):
        if p <= m or p <= n:
            a = 0
            b = 0
            mm = m
            nn = n
            while mm%p == 0:
                a += 1
                mm = mm/p
            while nn%p == 0:
                b += 1
                nn = nn/p
            q = q * (math.pow(p,max(a,b)))
    return q


print r_disivible_by_both(2,3)
