#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct SCC {
	int n, scc_cnt, dfs_cnt;
	vector<vector<int>> adj;
	vector<int> scc, dfs_order;
	stack<int> S;
	SCC(int n) :
		n(n), scc_cnt(0), dfs_cnt(0),
		adj(n + 1), scc(n + 1), dfs_order(n + 1) {
	}
	void AddEdge(int a, int b) { adj[a].push_back(b); }
	int DFS(int cur) {
		int ret = dfs_order[cur] = ++dfs_cnt; S.push(cur);
		for (const auto& nxt : adj[cur]) {
			if (!dfs_order[nxt]) ret = min(ret, DFS(nxt));
			else if (!scc[nxt]) ret = min(ret, dfs_order[nxt]);
		}
		if (ret == dfs_order[cur]) {
			for (scc_cnt++; S.size();) {
				int t = S.top(); S.pop();
				scc[t] = scc_cnt;
				if (t == cur) break;
			}
		}
		return ret;
	}
	void GetSCC() {
		for (int i = 1; i <= n; i++) if (!dfs_order[i]) DFS(i);
	}
};

int main() {
	fastio;
	// input
	int n, m; cin >> n >> m;
	SCC S(n);
	for (int a, b; m-- && cin >> a >> b; S.AddEdge(a, b));
	int k; cin >> k;

	// Get SCC
	S.GetSCC();
	const auto& scc = S.scc;
	const int V = S.scc_cnt;
	vector<vector<int>> adj(V + 1), rev(V + 1);

	// Get SCC Graph
	for (int i = 1; i <= n; i++) for (const auto& j : S.adj[i]) {
		if (scc[i] != scc[j]) {
			adj[scc[i]].push_back(scc[j]);
			rev[scc[j]].push_back(scc[i]);
		}
	}
	for (int i = 1; i <= V; i++) {
		sort(adj[i].begin(), adj[i].end());
		adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
		sort(rev[i].begin(), rev[i].end());
		rev[i].erase(unique(rev[i].begin(), rev[i].end()), rev[i].end());
	}

	// set sz, check
	vector<int> sz(V + 1), check(V + 1);
	for (int i = 1; i <= n; i++) sz[scc[i]]++;
	auto DFS = [&](int cur, auto&& DFS) -> void {
		check[cur] = 1;
		for (const auto& nxt : rev[cur]) {
			if (!check[nxt]) DFS(nxt, DFS);
		}
	};
	DFS(scc[k], DFS);

	// Get DP
	vector<int> cache(V + 1, -1);
	auto DP = [&](int cur, auto&& DP) -> int {
		if (!check[cur]) return -1;
		int& ret = cache[cur];
		if (ret != -1) return ret; ret = 0;
		for (const auto& nxt : adj[cur]) {
			const int t = DP(nxt, DP);
			if (t != -1) ret = max(ret, t);
		}
		return ret += sz[cur];
	};

	// Sol
	int idx = -1, mx = -1;
	for (int i = 1, bias = sz[scc[k]] > 1 ? 1 : 2; i <= n; i++) {
		if (i == k) continue;
		const int t = DP(scc[i], DP);
		if (t != -1 && mx < t - bias) idx = i, mx = t - bias;
	}
	if (idx == -1 || mx == 0) cout << 0 << '\n';
	else cout << idx << ' ' << mx << '\n';
}