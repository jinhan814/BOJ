#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, st, dist[100'001];
vector<int> adj[100'001];

int DFS(int cur, int prv, int dep) {
	if (dist[cur] <= dep) return 1;
	int ret = 0;
	for (const auto& nxt : adj[cur]) if (nxt ^ prv) ret += DFS(nxt, cur, dep + 1);
	return ret;
}

int main() {
	fastio;
	cin >> n >> st;
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	queue<int> Q;
	for (int i = 1; i <= n; i++) if (adj[i].size() == 1) Q.push(i), dist[i] = 1;
	while (Q.size()) {
		auto cur = Q.front(); Q.pop();
		for (const auto& nxt : adj[cur]) if (!dist[nxt]) Q.push(nxt), dist[nxt] = dist[cur] + 1;
	}
	cout << DFS(st, -1, 1) << '\n';
}