#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 0x3f3f3f3f;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

int n, m, dist1[1001], dist2[1001], dist3[1001];
vector<pii> adj[1001];
vector<tii> E;

int Dijkstra(int st, int dist[], int a = -1, int b = -1) {
	memset(dist + 1, 0x3f, n << 2);
	priority_queue<pii, vector<pii>, greater<pii>> PQ;
	PQ.push({ dist[st] = 0, st });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (const auto& [nxt, cost] : adj[cur]) {
			if (cur == a && nxt == b) continue;
			if (dist[nxt] > cdist + cost)
				PQ.push({ dist[nxt] = cdist + cost, nxt });
		}
	}
	return dist[n];
}

int Sol() {
	int mx = -1; Dijkstra(1, dist1), Dijkstra(n, dist2);
	for (auto& [a, b, c] : E) {
		if (dist1[a] > dist1[b]) swap(a, b);
		if (dist1[a] + c + dist2[b] != dist1[n]) continue;
		const int t = Dijkstra(1, dist3, a, b);
		mx = max(mx, Dijkstra(1, dist3, a, b));
	}
	return mx;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int a, b, c; m-- && cin >> a >> b >> c;) {
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
		E.push_back({ a, b, c });
	}
	cout << Sol() << '\n';
}