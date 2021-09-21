#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t
constexpr int INF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

int n, m, cnt, dist[501], inque[501];
vector<pii> adj[501];

int32_t main() {
	fastio;
	cin >> n >> m;
	while (m--) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
	}

	memset(dist, 0x3f, sizeof dist);
	memset(inque, -1, sizeof inque);
	queue<int> Q;
	dist[1] = 0; inque[1] = 0; Q.push(1);
	for (; Q.size() && cnt < n; Q.size() && cnt++) {
		for (int i = Q.size(); i --> 0;) {
			auto cur = Q.front(); Q.pop(); inque[cur] = -1;
			for (const auto& [nxt, cost] : adj[cur]) {
				if (dist[nxt] > dist[cur] + cost) {
					dist[nxt] = dist[cur] + cost;
					if (inque[nxt] != cnt) Q.push(nxt), inque[nxt] = cnt;
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