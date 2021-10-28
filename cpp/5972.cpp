#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int n, m, dist[50'001];
vector<pii> adj[50'001];

int Dijkstra() {
	memset(dist + 1, 0x3f, n << 2);
	priority_queue<pii, vector<pii>, greater<>> PQ;
	PQ.push({ dist[1] = 0, 1 });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (const auto& [nxt, cost] : adj[cur])
			if (dist[nxt] > cdist + cost) PQ.push({ dist[nxt] = cdist + cost, nxt });
	}
	return dist[n];
}

int main() {
	fastio;
	cin >> n >> m;
	while (m--) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}
	cout << Dijkstra() << '\n';
}