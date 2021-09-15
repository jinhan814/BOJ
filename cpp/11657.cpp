#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t
constexpr int INF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

int n, m, cnt, dist[501], inqueue[501];
vector<pii> adj[501];

int32_t main() {
	fastio;
	cin >> n >> m;
	while (m--) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
	}

	memset(dist, 0x3f, sizeof dist);
	queue<int> Q;
	dist[1] = 0; inqueue[1] = 1; Q.push(1);
	for (; Q.size() && cnt < n; Q.size() && cnt++) {
		for (int i = Q.size(); i --> 0;) {
			auto cur = Q.front(); Q.pop(); inqueue[cur] = 0;
			for (const auto& [nxt, cost] : adj[cur]) {
				if (dist[nxt] > dist[cur] + cost) {
					dist[nxt] = dist[cur] + cost;
					if (!inqueue[nxt]) Q.push(nxt), inqueue[nxt] = 1;
				}
			}
		}
	}

	if (cnt == n) cout << -1 << '\n';
	else {
		for (int i = 2; i <= n; i++)
			cout << (dist[i] == INF ? -1 : dist[i]) << '\n';
	}
}