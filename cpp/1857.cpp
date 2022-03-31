#include<bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;
using i64 = long long;

int n, m, v[30][30];
int st, en, dist[900]; i64 DP[900];
vector<int> adj[900];
bitset<900> visited;

void SetEdge(int x, int y) {
	queue<pii> Q; visited.reset();
	Q.push({ x, y }), visited[x * m + y] = 1;
	while (Q.size()) {
		auto [cx, cy] = Q.front(); Q.pop();
		for (int d = 0; d < 8; d++) {
			const int nx = cx + "10013443"[d] - '2';
			const int ny = cy + "43100134"[d] - '2';
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (v[nx][ny] == 2 || visited[nx * m + ny]) continue;
			if (v[nx][ny] && v[nx][ny] != 4) Q.push({ nx, ny }), visited[nx * m + ny] = 1;
			else adj[x * m + y].push_back(nx * m + ny), visited[nx * m + ny] = 1;
		}
	}
}

void BFS() {
	memset(dist, -1, sizeof dist);
	queue<int> Q; visited.reset();
	Q.push(st), visited[st] = 1, dist[st] = 0, DP[st] = 1;
	while (Q.size()) {
		auto cur = Q.front(); Q.pop();
		for (const auto& nxt : adj[cur]) {
			if (!visited[nxt]) Q.push(nxt), visited[nxt] = 1, dist[nxt] = dist[cur] + 1;
			if (dist[nxt] == dist[cur] + 1) DP[nxt] += DP[cur];
		}
	}
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		cin >> v[i][j];
		if (v[i][j] == 3) st = i * m + j;
		else if (v[i][j] == 4) en = i * m + j;
	}
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (v[i][j] != 2) SetEdge(i, j);
	BFS();
	if (dist[en] == -1) cout << -1 << '\n';
	else cout << dist[en] - 1 << '\n' << DP[en] << '\n';
}