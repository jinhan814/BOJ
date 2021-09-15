#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, v[200], w[200];
vector<int> adj[200];
int64_t cache[200][2];

int64_t DFS(int cur, int prv, bool flag) {
	auto& ret = cache[cur][flag];
	if (ret != -1) return ret;
	ret = flag ? v[cur] : 0;
	for (const auto& nxt : adj[cur]) {
		if (nxt == prv) continue;
		if (flag) ret += DFS(nxt, cur, 0);
		else ret += max(DFS(nxt, cur, 0), DFS(nxt, cur, 1));
	}
	return ret;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 0; i < m; i++) cin >> w[i];
	sort(v, v + n);

	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		auto idx = lower_bound(v, v + n, v[i] - w[j]) - v;
		if (idx != n && v[idx] == v[i] - w[j])
			adj[i].push_back(idx), adj[idx].push_back(i);
	}

	memset(cache, -1, sizeof cache);
	cout << max(DFS(0, -1, 0), DFS(0, -1, 1)) << '\n';
}