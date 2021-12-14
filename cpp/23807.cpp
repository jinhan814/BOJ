#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

constexpr int INF = int(1e18) + 7;
using pii = pair<int, int>;

int n, m, k, st, en, dist[3][100'001];
vector<pii> adj[100'001];
vector<int> v;

void Dijkstra(int st, int idx) {
    fill(dist[idx] + 1, dist[idx] + 1 + n, INF);
	priority_queue<pii, vector<pii>, greater<pii>> PQ;
    PQ.push({ dist[idx][st] = 0, st });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[idx][cur] != cdist) continue;
		for (const auto& [nxt, cost] : adj[cur])
			if (dist[idx][nxt] > cdist + cost)
				PQ.push({ dist[idx][nxt] = cdist + cost, nxt });
	}
}

int Sol() {
	int ret = INF; Dijkstra(st, 1), Dijkstra(en, 2);
	if (dist[1][en] == INF) return -1;
	for (auto& a : v) if (dist[1][a] != INF && dist[2][a] != INF) {
		Dijkstra(a, 0);
		for (auto& b : v) if (a != b && dist[1][b] != INF && dist[0][b] != INF)
			for (auto& c : v) if (a != c && b != c && dist[2][c] != INF && dist[0][c] != INF)
				ret = min(ret, dist[1][b] + dist[0][b] + dist[0][c] + dist[2][c]);
	}
	return ret ^ INF ? ret : -1;
}

int32_t main() {
	fastio;
	cin >> n >> m;
	for (int i = m, a, b, c; i-- && cin >> a >> b >> c;) {
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}
	cin >> st >> en >> k;
	for (int i = k, t; i-- && cin >> t; v.push_back(t));
	cout << Sol() << '\n';
}