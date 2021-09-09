import sys
input = lambda: sys.stdin.readline().rstrip()

def conv(c):
    if c == 'R': return 0
    if c == 'S': return 1
    return 2

for _ in range(int(input())):
    n = int(input())
    v = [input() for _ in range(n)]
    check = [0] * n

    for i in range(len(v[0])):
        cur = [0] * 3
        for j in range(n):
            if not check[j]:
                cur[conv(v[j][i])] = 1
        if sum(cur) != 2: continue
        win = 0 if cur[0] and cur[1] else 1 if cur[1] and cur[2] else 2
        for j in range(n):
            if not check[j] and conv(v[j][i]) != win:
                check[j] = 1

    print(check.index(0) + 1 if sum(check) == n - 1 else 0)