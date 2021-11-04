import sys
from decimal import *
input = sys.stdin.readline

getcontext().prec = 50
getcontext().rounding = ROUND_HALF_UP

A, B, C = map(Decimal, map(int, input().split()))
PI = Decimal('3.14159265358979323846264338327950288419716939937510')

def Sin(x):
    x = x % (2 * PI)
    getcontext().prec += 2
    i, lasts, s, fact, num, sign = 1, 0, x, 1, x, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i - 1)
        num *= x * x
        sign *= -1
        s += num / fact * sign
    getcontext().prec -= 2
    return +s

lo, hi = (C - B) / A, (C + B) / A

while hi - lo > Decimal(1e-21):
    mid = (lo + hi) / 2
    if A * mid + B * Sin(mid) < C: lo = mid
    else: hi = mid

print(round(lo, 6))