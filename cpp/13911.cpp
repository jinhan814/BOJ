#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int V, E, n, m, L1, L2, mn = 1e9;
int dist1[10'001], dist2[10'001];
vector<pii> adj[10'001];
priority_queue<pii, vector<pii>, greater<>> PQ;

void Dijkstra(int dist[]) {
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		for (const auto& [nxt, cost] : adj[cur]) {
			if (dist[nxt] > cdist + cost)
				PQ.push({ dist[nxt] = cdist + cost, nxt });
		}
	}
}

int main() {
	fastio;
	cin >> V >> E;
	for (int i = 0; i < E; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}

	cin >> n >> L1;
	memset(dist1, 0x3f, sizeof dist1);
	for (int i = 0; i < n; i++) {
		int t; cin >> t;
		PQ.push({ dist1[t] = 0, t });
	}
	Dijkstra(dist1);

	cin >> m >> L2;
	memset(dist2, 0x3f, sizeof dist2);
	for (int i = 0; i < m; i++) {
		int t; cin >> t;
		PQ.push({ dist2[t] = 0, t });
	}
	Dijkstra(dist2);

	for (int i = 1; i <= V; i++) {
		if (!dist1[i] || !dist2[i]) continue;
		if (dist1[i] > L1 || dist2[i] > L2) continue;
		mn = min(mn, dist1[i] + dist2[i]);
	}
	cout << (mn == 1e9 ? -1 : mn) << '\n';
}