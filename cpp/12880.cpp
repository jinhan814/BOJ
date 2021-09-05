#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define all(v) (v).begin(), (v).end()
#define compress(v) sort(all(v)), (v).erase(unique(all(v)), (v).end())

int n, v[51][51];
vector<int> I;

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
		if (I[l] <= v[i][j] && v[i][j] <= I[r]) S.addEdge(i, j);
	}
	S.GetSCC();

	bool ret = 1;
	for (int i = 1; i <= n; i++) if (S.scc[1] != S.scc[i]) ret = 0;
	return ret;
}

int main() {
	fastio;
	cin >> n;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
		cin >> v[i][j];
		I.push_back(v[i][j]);
	}
	compress(I);

	int mn = 1e9;
    for (int l = 0, r = 0; l < I.size(); l++) {
        while (r < I.size() && !Check(l, r)) r++;
        if (r < I.size()) mn = min(mn, I[r] - I[l]);
    }
	cout << mn << '\n';
}