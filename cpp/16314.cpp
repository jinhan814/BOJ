#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, st;
vector<int> leaf, adj[100'000];

void DFS(int cur, int prv = -1) {
	if (adj[cur].size() == 1) leaf.push_back(cur);
	for (const auto& nxt : adj[cur]) if (nxt != prv) DFS(nxt, cur);
}

int main() {
	fastio;
	cin >> n >> st;
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	DFS(st); const int sz = leaf.size();
	cout << (sz + 1) / 2 << '\n';
	for (int i = 0; i < sz / 2; i++) cout << leaf[i] << ' ' << leaf[i + sz / 2] << '\n';
	if (sz & 1) cout << leaf[0] << ' ' << leaf.back() << '\n';
}