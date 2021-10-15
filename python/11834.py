import sys
input = sys.stdin.readline

n = int(input())

lo, hi = 0, n
while lo + 1 < hi:
    mid = (lo + hi) // 2
    if mid * (mid + 1) >> 1 < n: lo = mid
    else: hi = mid

print(2 * n - hi)