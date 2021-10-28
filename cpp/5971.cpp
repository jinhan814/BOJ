#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, q, par[1001], dep[1001];
vector<int> adj[1001];

void DFS(int cur) {
	for (const auto& nxt : adj[cur])
		dep[nxt] = dep[cur] + 1, DFS(nxt);
}

int LCA(int a, int b) {
	if (dep[a] != dep[b]) {
		if (dep[a] < dep[b]) swap(a, b);
		while (dep[a] > dep[b]) a = par[a];
	}
	while (a != b) a = par[a], b = par[b];
	return a;
}

int main() {
	fastio;
	cin >> n >> q;
	for (int i = 2; i <= n; i++) {
		cin >> par[i];
		adj[par[i]].push_back(i);
	}
    for (DFS(1); q--;) {
		int a, b; cin >> a >> b;
		cout << LCA(a, b) << '\n';
	}
}