import sys
input = sys.stdin.readline
sys.setrecursionlimit(int(1e6))

n = int(input())
v = [*map(int, input().split())]
DP = [0] * n # DP[i] : i번 원소로 '끝나는' LIS의 길이

def Sol(i):
    if DP[i]: return DP[i]
    DP[i] = 1
    for j in range(i):
        if v[j] < v[i]: DP[i] = max(DP[i], Sol(j) + 1)
    return DP[i]

print(max(Sol(i) for i in range(n)))