#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

constexpr int INF = int(1e18) + 7;
using pii = pair<int, int>;

int n, m, k, st, en, C[22][22], DP[20][1 << 20];
vector<pair<int, int>> adj[100'000];
vector<int> v;

void Dijkstra(int st, vector<int>& dist) {
	fill(dist.begin(), dist.end(), INF);
	priority_queue<pii, vector<pii>, greater<>> PQ; PQ.push({ dist[st] = 0, st });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (auto& [nxt, cost] : adj[cur]) {
			if (dist[nxt] > cdist + cost)
				PQ.push({ dist[nxt] = cdist + cost, nxt });
		}
	}
}

void Init() {
	vector<int> dist(n);
	for (int i = 0; i < v.size(); i++) {
		Dijkstra(v[i], dist);
		for (int j = 0; j < v.size(); j++) C[i][j] = dist[v[j]];
	}
}

int Sol(int cur, int state) {
	if (state == (1 << k) - 1) return C[cur][k + 1];
	int& ret = DP[cur][state];
	if (ret != -1) return ret; ret = INF;
	for (int i = 0; i < k; i++) if (~state & 1 << i) {
		auto res = Sol(i, state | 1 << i);
		if (res != INF) ret = min(ret, res + C[cur][i]);
	}
	return ret;
}

int32_t main() {
	fastio;
	cin >> n >> m;
	while (m--) {
		int a, b, c; cin >> a >> b >> c; --a, --b;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}
	cin >> st >> en >> k; --st, --en, v.resize(k);
	for (int i = 0; i < k; i++) cin >> v[i], --v[i];
	v.push_back(st), v.push_back(en), Init();

	int ans = INF; memset(DP, -1, sizeof DP);
	for (int i = 0; i < k; i++) {
		auto res = Sol(i, 1 << i);
		if (res != INF) ans = min(ans, res + C[k][i]);
	}
	cout << (ans == INF ? -1 : ans) << '\n';
}