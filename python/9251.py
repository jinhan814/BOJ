import sys
input = lambda: sys.stdin.readline().rstrip()
sys.setrecursionlimit(int(1e5))

a = input()
b = input()
DP = [[-1] * len(b) for _ in range(len(a))]

def Sol(i, j):
    if i < 0 or j < 0: return 0
    if DP[i][j] != -1: return DP[i][j]
    DP[i][j] = 0
    if a[i] == b[j]: DP[i][j] = Sol(i - 1, j - 1) + 1
    else: DP[i][j] = max(Sol(i - 1, j), Sol(i, j - 1))
    return DP[i][j]

print(Sol(len(a) - 1, len(b) - 1))