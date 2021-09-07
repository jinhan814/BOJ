#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;
using pii = pair<int, int>;
using vi = vector<int>;
using vvp = vector<vector<pii>>;

int main() {
	fastio;
	for (int n, m; cin >> n >> m && n;) {
		//input
		int st, en; cin >> st >> en;
		vvp adj(n), rev(n); vi dist1(n, INF), dist2(n, INF), dist3(n, INF);
		while (m--) {
			int a, b, c; cin >> a >> b >> c;
			adj[a].push_back({ b, c });
			rev[b].push_back({ a, c });
		}

		//dijkstra
		auto Dijkstra = [&](auto& adj, auto& dist, int st) -> void {
			priority_queue<pii, vector<pii>, greater<pii>> PQ;
			dist[st] = 0; PQ.push({ dist[st], st });
			while (PQ.size()) {
				auto [cdist, cur] = PQ.top(); PQ.pop();
				if (dist[cur] != cdist) continue;
				for (const auto& [nxt, cost] : adj[cur]) {
					if (dist[nxt] > cdist + cost) {
						dist[nxt] = cdist + cost;
						PQ.push({ dist[nxt], nxt });
					}
				}
			}
		};
		Dijkstra(adj, dist1, st); Dijkstra(rev, dist2, en);

		//dijkstra2
		priority_queue<pii, vector<pii>, greater<pii>> PQ;
		dist3[st] = 0; PQ.push({ dist3[st], st });
		while (PQ.size()) {
			auto [cdist, cur] = PQ.top(); PQ.pop();
			if (dist3[cur] != cdist) continue;
			for (const auto& [nxt, cost] : adj[cur]) {
				if (dist1[cur] + cost + dist2[nxt] == dist1[en]) continue;
				if (dist3[nxt] > cdist + cost) {
					dist3[nxt] = cdist + cost;
					PQ.push({ dist3[nxt], nxt });
				}
			}
		}

		cout << (dist3[en] == INF ? -1 : dist3[en]) << '\n';
	}
}