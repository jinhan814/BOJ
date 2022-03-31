#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int n, m, cnt, dist[21][21];
pii pos[21];
map<int, int> M;
bitset<1'000'000> B, C, visited;

void BFS(int st) {
	visited.reset();
	queue<pii> Q; Q.push(pos[st]), visited[pos[st].first * m + pos[st].second] = 1;
	for (int d = 0, t = 0; Q.size(); d++) {
		for (int _ = Q.size(); _--;) {
			auto [x, y] = Q.front(); Q.pop();
			if (C[x * m + y] && st < M[x * m + y]) {
                dist[st][M[x * m + y]] = dist[M[x * m + y]][st] = d;
                if (++t == cnt - st) return;
            }
			for (int i = 0; i < 4; i++) {
				const int nx = x + "1012"[i] - '1';
				const int ny = y + "2101"[i] - '1';
				if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				if (B[nx * m + ny] || visited[nx * m + ny]) continue;
				Q.push({ nx, ny }), visited[nx * m + ny] = 1;
			}
		}
	}
}

int DFS(int cur) {
	static int state = 0;
	if (__builtin_popcount(state) == 5) return 0;
	int ret = 1e9;
	for (int nxt = 1; nxt <= cnt; nxt++) {
		if (state & 1 << nxt || dist[cur][nxt] == -1) continue;
		state ^= 1 << nxt;
		ret = min(ret, DFS(nxt) + dist[cur][nxt]);
		state ^= 1 << nxt;
	}
	return ret;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		for (int j = 0; j < m; j++) {
			if (s[j] == 'X') B[i * m + j] = 1;
			else if (s[j] == 'S') s[j] = 0, pos[0] = { i, j }, C[i * m + j] = 1;
			else if (s[j] == 'K') s[j] = ++cnt, pos[cnt] = { i, j }, C[i * m + j] = 1;
		}
	}
	for (int i = 0; i <= cnt; i++) M[pos[i].first * m + pos[i].second] = i;
	memset(dist, -1, sizeof dist);
	for (int i = 0; i <= cnt; i++) BFS(i);
	auto res = DFS(0);
	if (res == 1e9) res = -1;
	cout << res << '\n';
}