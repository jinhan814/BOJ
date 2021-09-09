import sys
from collections import deque
input = lambda: sys.stdin.readline().rstrip()

v = [input() for _ in range(10)]
dist = [[-1] * 10 for _ in range(10)]
ex, ey = 0, 0

for i in range(10):
    for j in range(10):
        if v[i][j] == 'L': ex, ey = i, j
        if v[i][j] != 'B': continue
        Q = deque([(i, j)]); dist[i][j] = 0
        while Q:
            x, y = Q.popleft()
            for dx, dy in [(0, 1), (-1, 0), (0, -1), (1, 0)]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < 10 and 0 <= ny < 10 and v[nx][ny] != 'R' and not ~dist[nx][ny]:
                    Q.append((nx, ny))
                    dist[nx][ny] = dist[x][y] + 1

print(dist[ex][ey] - 1)