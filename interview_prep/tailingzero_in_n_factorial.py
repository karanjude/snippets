def fact(n):
    if n < 0:
        return 0
    i = 5
    cnt = 0
    while n/i > 0:
        cnt += n/i
        i *= 5
    return cnt

print fact(6)
print fact(26)
