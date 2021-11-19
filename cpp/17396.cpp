#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

using pii = pair<int, int>;

int n, m, v[100'000], dist[100'000];
vector<pii> adj[100'000];

int Dijkstra() {
	memset(dist, 0x3f, sizeof dist);
	priority_queue<pii, vector<pii>, greater<>> PQ;
	PQ.push({ dist[0] = 0, 0 });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (const auto& [nxt, cost] : adj[cur]) {
			if (nxt != n - 1 && v[nxt] || dist[nxt] <= cdist + cost) continue;
			PQ.push({ dist[nxt] = cdist + cost, nxt });
		}
	}
	return dist[n - 1] == 0x3f3f3f3f3f3f3f3f ? -1 : dist[n - 1];
}

int32_t main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> v[i];
	while (m--) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}
	cout << Dijkstra() << '\n';
}