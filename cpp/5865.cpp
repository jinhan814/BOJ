#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int n, m, X, mn = 1e18, dist[50'001];
vector<tuple<int, int, int>> adj[50'001];
vector<int> L;

int Dijkstra(int lim) {
	memset(dist, 0x3f, sizeof dist);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> PQ;
	PQ.push({ dist[1] = 0, 1 });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (const auto& [nxt, cost, sz] : adj[cur])
			if (sz >= lim && dist[nxt] > cdist + cost)
				PQ.push({ dist[nxt] = cdist + cost, nxt });
	}
	return dist[n] + X / lim;
}

int32_t main() {
	fastio;
	cin >> n >> m >> X;
	while (m--) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		adj[a].push_back({ b, c, d });
		adj[b].push_back({ a, c, d });
		L.push_back(d);
	}
	for (auto& i : L) mn = min(mn, Dijkstra(i));
	cout << mn << '\n';
}