#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

int n, m, ind[200'001], DP[200'001], prv[200'001];
i64 dist[200'001];
vector<pair<int, int>> G[200'001];
bitset<200'001> B;

void Dijkstra() {
	memset(dist, 0x3f, sizeof dist);
	priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> PQ;
	PQ.push({ dist[1] = 0, 1 });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (auto& [nxt, cost] : G[cur]) {
			if (dist[nxt] > cdist + cost)
				PQ.push({ dist[nxt] = cdist + cost, nxt });
		}
	}
}

void DFS(int cur) {
	for (const auto& [nxt, cost] : G[cur]) {
		if (dist[nxt] != dist[cur] + cost) continue;
		if (!ind[nxt]++) DFS(nxt);
	}
}

void BFS() {
	memset(prv, -1, sizeof prv);
	queue<int> Q; Q.push(1);
	while (Q.size()) {
		auto cur = Q.front(); Q.pop();
		if (B[cur]) DP[cur]++;
		for (const auto& [nxt, cost] : G[cur]) {
			if (dist[nxt] != dist[cur] + cost) continue;
			if (DP[nxt] <= DP[cur]) DP[nxt] = DP[cur], prv[nxt] = cur;
			if (!--ind[nxt]) Q.push(nxt);
		}
	}
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int a, b, c; cin >> a >> b >> c;
		G[a].push_back({ b, c });
		G[b].push_back({ a, c });
	}
	for (int i = 1; i <= n; i++) {
		int t; cin >> t;
		B[i] = t;
	}
	Dijkstra(); DFS(1); BFS();
	if (DP[n] != B.count()) cout << -1 << '\n';
	else {
		vector<int> path;
		for (int i = n; ~i; i = prv[i]) path.push_back(i);
		cout << path.size() << '\n';
		for (int i = path.size(); i--;) cout << path[i] << ' '; cout << '\n';
	}
}