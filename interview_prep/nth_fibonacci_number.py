def fib(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    if n > 1:
        return fib(n-1) + fib(n-2)
    else:
        return -1

for i in range(1,10):
    print fib(i)
