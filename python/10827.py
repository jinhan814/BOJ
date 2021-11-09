import sys
from decimal import *
input = sys.stdin.readline

getcontext().prec = 1200

def Pow(x, n):
    ret = Decimal(1)
    while n:
        if n & 1: ret *= x
        x *= x; n >>= 1
    return ret

a, b = map(Decimal, input().split())
print(f'{Pow(a, int(b)):f}')