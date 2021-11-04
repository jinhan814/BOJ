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

int main() {
	fastio;
	cin >> n >> m;
	while (m--) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	DFS1(1, -1); DFS2(1);
	bool flag = 1;
	for (int i = 1; i <= n; i++) if (DP[i] > 1) flag = 0;
	cout << (flag ? "Cactus" : "Not cactus") << '\n';
}