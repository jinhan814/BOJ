#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;
using pii = pair<int, int>;

int main() {
	fastio;
	// 1. input
	int n, m; cin >> n >> m;
	int st, en, a, b; cin >> st >> en >> a >> b;
	vector<int> v(b), w(m), D(m, INF);
	vector<vector<pii>> adj(n + 1);
	map<pii, int> I;
	for (int i = 0; i < b; i++) cin >> v[i];
	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
		I[{ a, b }] = I[{ b, a }] = i, w[i] = c;
	}

	// 2. init D[i]
	for (int i = 1, t = 0; i < b; i++) {
		const int idx = I[{ v[i - 1], v[i]}];
		D[idx] = t, t += w[idx];
	}

	// 3. Dijkstra
	vector<int> dist(n + 1, INF);
	priority_queue<pii, vector<pii>, greater<pii>> PQ;
	PQ.push({ dist[st] = a, st });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (const auto& [nxt, cost] : adj[cur]) {
			int ndist = cdist + cost;
			const int idx = I[{ cur, nxt }];
			if (D[idx] <= cdist && cdist < D[idx] + cost) ndist = D[idx] + 2 * cost;
			if (dist[nxt] > ndist) PQ.push({ dist[nxt] = ndist, nxt });
		}
	}
	cout << dist[en] - a << '\n';
}