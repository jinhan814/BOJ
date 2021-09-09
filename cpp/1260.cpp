#include <unistd.h>
#define SZ (1 << 12)

// FastIO Implementation
char r[SZ], *w = r, *p = r + SZ, *q = r;
char ReadChar() {
    if (p - r >= SZ) read(0, p = r, SZ);
    return *p++;
}
int ReadInt() {
    int ret = 0;
    for (char c = ReadChar(); c & 16; ret = 10 * ret + (c & 15), c = ReadChar());
    return ret;
}
void WriteChar(char c) {
    if (q - w >= SZ) write(1, w, q - w), q = w;
    *q++ = c;
}
void WriteInt(int n) {
    int sz = 1, t = n;
    for (; t >= 10; t /= 10) sz++;
    if (q + sz - w >= SZ) write(1, w, q - w), q = w;
    for (int i = sz; i --> 0; n /= 10) q[i] = n % 10 | 48;
    q += sz;
}

// Graph Traversal Implementation
short n, m, st, Q[1001], s, e;
int adj[1001][32], visited[32];

void DFS(int cur) {
    WriteInt(cur), WriteChar(' '); visited[cur >> 5] |= 1 << (cur & 31);
    for (int i = 1; i <= n; i++) {
        if ((adj[cur][i >> 5] & (1 << (i & 31))) && (~visited[i >> 5] & (1 << (i & 31)))) DFS(i);
    }
}
void BFS(int st) {
    for (int i = 0; i < 32; i++) visited[i] = 0;
    Q[e++] = st, visited[st >> 5] |= 1 << (st & 31);
    while (s < e) {
        int cur = Q[s++]; WriteInt(cur), WriteChar(' ');
        for (int i = 1; i <= n; i++) {
            if ((adj[cur][i >> 5] & (1 << (i & 31))) && (~visited[i >> 5] & (1 << (i & 31)))) {
                Q[e++] = i, visited[i >> 5] |= 1 << (i & 31);
            }
        }
    }
}

int main() {
    n = ReadInt(), m = ReadInt(), st = ReadInt();
    while (m--) {
        int a = ReadInt(), b = ReadInt();
        adj[a][b >> 5] |= 1 << (b & 31);
        adj[b][a >> 5] |= 1 << (a & 31);
    }
    DFS(st); WriteChar('\n');
    BFS(st); WriteChar('\n');
	write(1, w, q - w); _exit(0);
}