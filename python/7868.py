import sys
from heapq import *
input = sys.stdin.readline

*v, = map(int, input().split())
PQ = []

t1 = 1
for i in range(100):
    t2 = 1
    if t1 >= 1e18: break
    for j in range(100):
        t3 = 1
        if t1 * t2 >= 1e18: break
        for k in range(100):
            if t1 * t2 * t3 >= 1e18: break
            heappush(PQ, -t1 * t2 * t3)
            if len(PQ) > v[3] + 1: heappop(PQ)
            t3 *= v[2]
        t2 *= v[1]
    t1 *= v[0]

print(-PQ[0])