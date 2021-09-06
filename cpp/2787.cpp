#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

struct HopcroftKarp { //Hopcroft-Karp algorithm, O(Esqrt(V)).
	vector<vector<int>> adj;
	vector<int> par, lv, work, check; int sz;
	HopcroftKarp(int n) : adj(n), par(n, -1), lv(n), work(n), check(n), sz(n) {}
	void add_edge(int a, int b) { adj[a].push_back(b); }
	void BFS() {
		queue<int> Q;
		for (int i = 0; i < sz; i++) {
			if (!check[i]) lv[i] = 0, Q.push(i);
			else lv[i] = INF;
		}
		while (!Q.empty()) {
			auto cur = Q.front(); Q.pop();
			for (auto nxt : adj[cur]) {
				if (par[nxt] != -1 && lv[par[nxt]] == INF) {
					lv[par[nxt]] = lv[cur] + 1;
					Q.push(par[nxt]);
				}
			}
		}
	}
	bool DFS(int cur) {
		for (int& i = work[cur]; i < adj[cur].size(); i++) {
			int nxt = adj[cur][i];
			if (par[nxt] == -1 || lv[par[nxt]] == lv[cur] + 1 && DFS(par[nxt])) {
				check[cur] = 1, par[nxt] = cur;
				return 1;
			}
		}
		return 0;
	}
	int Match() {
		int ret = 0;
		for (int fl = 0; ; fl = 0) {
			fill(work.begin(), work.end(), 0); BFS();
			for (int i = 0; i < sz; i++) if (!check[i] && DFS(i)) fl++;
			if (!fl) break;
			ret += fl;
		}
		return ret;
	}
};

bitset<201> check[201];

int main() {
	fastio;
	int n, m; cin >> n >> m;
	vector<int> mx(n + 1, n), mn(n + 1, 1);
	while (m--) {
		int t, a, b, c; cin >> t >> a >> b >> c;
		for (int i = a; i <= b; i++) {
			if (t & 1) mx[i] = min(mx[i], c);
			else mn[i] = max(mn[i], c);
		}
		for (int i = 1; i < a; i++) check[i][c] = 1;
		for (int i = b + 1; i <= n; i++) check[i][c] = 1;
	}

	HopcroftKarp flow(2 * n + 1);
	for (int i = 1; i <= n; i++)
		for (int j = mn[i]; j <= mx[i]; j++)
			if (!check[i][j]) flow.add_edge(i, n + j);

	if (flow.Match() == n) {
		vector<int> ans(n + 1);
		for (int i = 1; i <= n; i++) ans[flow.par[n + i]] = i;
		for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
		cout << '\n';
	}
	else cout << -1 << '\n';
}