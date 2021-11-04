#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, DP[100'001], par[100'001];
int dfs_cnt, dfs_order[100'001];
vector<int> adj[100'001];

void DFS1(int cur, int prv) {
	dfs_order[cur] = ++dfs_cnt;
	for (const auto& nxt : adj[cur]) {
		if (nxt == prv) continue;
		if (!dfs_order[nxt]) par[nxt] = cur, DFS1(nxt, cur);
		else if (dfs_order[nxt] < dfs_order[cur]) DP[cur]++, DP[par[nxt]]--;
	}
}

int DFS2(int cur) {
	int& ret = DP[cur];
	for (const auto& nxt : adj[cur]) {
		if (par[nxt] != cur) continue;
		ret += DFS2(nxt);
	}
	return ret;
}

bool DFS3(int cur) {
	if (DP[cur] > 1) return 1;
	for (const auto& nxt : adj[cur])
		if (par[nxt] == cur && DFS3(nxt)) return 1;
	return 0;
}

int main() {
	fastio;
	cin >> n >> m;
	while (m--) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (dfs_order[i]) continue;
		DFS1(i, -1); DFS2(i);
		if (!DFS3(i)) cnt++;
	}
	cout << cnt << '\n';
}