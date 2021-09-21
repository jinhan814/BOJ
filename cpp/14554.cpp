#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

constexpr int INF = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 1e9 + 9;
using pii = pair<int, int>;

int n, m, st, en, dist[100'001], DP[100'001];
vector<pii> adj[100'001];

int Dijkstra() {
	memset(dist, 0x3f, sizeof dist);
	priority_queue<pii, vector<pii>, greater<pii>> PQ;
	PQ.push({ dist[st] = 0, st }), DP[st] = 1;
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (const auto& [nxt, cost] : adj[cur]) {
			if (dist[nxt] < cdist + cost) continue;
			else if (dist[nxt] == cdist + cost) (DP[nxt] += DP[cur]) %= MOD;
			else PQ.push({ dist[nxt] = cdist + cost, nxt }), DP[nxt] = DP[cur];
		}
	}
	return DP[en];
}

int32_t main() {
	fastio;
	cin >> n >> m >> st >> en;
	while (m--) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}
	cout << Dijkstra() << '\n';
}