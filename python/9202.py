import sys
input = lambda: sys.stdin.readline().rstrip()

class TrieNode:
    def __init__(self):
        self.nxt = [0] * 26
        self.idx = -1

class Trie:
    def __init__(self):
        self.node = [TrieNode()]
    def Add(self, s, idx):
        cur = 0
        for c in s:
            if self.node[cur].nxt[ord(c) - 65] == 0:
                self.node[cur].nxt[ord(c) - 65] = len(self.node)
                self.node.append(TrieNode())
            cur = self.node[cur].nxt[ord(c) - 65]
        self.node[cur].idx = idx

n = int(input())
s = [input() for _ in range(n)]; input()

T = Trie()
board, v = [], {}
visited = [[0] * 4 for _ in range(4)]
for i in range(n): T.Add(s[i], i)

def DFS(x, y, pos):
    if T.node[pos].nxt[ord(board[x][y]) - 65] == 0: return
    pos = T.node[pos].nxt[ord(board[x][y]) - 65]; visited[x][y] = 1
    if T.node[pos].idx != -1: v.add(T.node[pos].idx)
    for dx, dy in ((0, 1), (-1, 1), (-1, 0), (-1, -1), (0, -1), (1, -1), (1, 0), (1, 1)):
        nx = x + dx; ny = y + dy
        if 0 <= nx < 4 and 0 <= ny < 4 and not visited[nx][ny]: DFS(nx, ny, pos)
    visited[x][y] = 0

def GetScore(n):
    if 3 <= n <= 4: return 1
    if n == 5: return 2
    if n == 6: return 3
    if n == 7: return 5
    if n == 8: return 11
    return 0

for _ in range(int(input())):
    board = [input() for _ in range(4)];
    v = set()
    for i in range(4):
        for j in range(4): DFS(i, j, 0)
    score, cnt, mx = 0, 0, ''
    for i in v:
        score += GetScore(len(s[i]))
        cnt += 1
        if len(mx) < len(s[i]) or len(mx) == len(s[i]) and mx > s[i]: mx = s[i]
    print(score, mx, cnt); input()
