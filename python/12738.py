import sys
input = sys.stdin.readline

def lower_bound(v, x):
    lo, hi = -1, len(v)
    while lo + 1 < hi:
        mid = lo + hi >> 1
        if v[mid] < x: lo = mid
        else: hi = mid
    return hi

n = int(input())
v = [*map(int, input().split())]
LIS = []

for i in range(n):
    if i == 0 or LIS[-1] < v[i]: LIS.append(v[i])
    else: LIS[lower_bound(LIS, v[i])] = v[i]

print(len(LIS))