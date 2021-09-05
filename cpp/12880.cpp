#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, v[51][51];

struct SCC {
	int n, scc_cnt, dfs_cnt;
	vector<vector<int>> adj;
	vector<int> scc, dfs_order;
	stack<int> S;
	SCC(int n) :
		n(n), scc_cnt(0), dfs_cnt(0),
		adj(n + 1), scc(n + 1), dfs_order(n + 1) {
	}
	void addEdge(int a, int b) { adj[a].push_back(b); }
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

bool Check(int l, int r) {
	SCC S(n);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
		if (l <= v[i][j] && v[i][j] <= r) S.addEdge(i, j);
	}
	S.GetSCC();

	bool ret = 1;
	for (int i = 1; i <= n; i++) if (S.scc[1] != S.scc[i]) ret = 0;
	return ret;
}

int main() {
	fastio;
	cin >> n;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> v[i][j];

	int mn = 1e9;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
		int lo = v[i][j] - 1, hi = 150'001;
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (!Check(v[i][j], mid)) lo = mid;
			else hi = mid;
		}
		if (hi != 150'001) mn = min(mn, hi - v[i][j]);
	}
	cout << mn << '\n';
}