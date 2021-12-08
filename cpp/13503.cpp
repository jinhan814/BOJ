#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

struct HopcroftKarp { // Hopcroft-Karp algorithm, O(Esqrt(V)).
	vector<vector<int>> adj;
	vector<int> par, lv, work, check; int sz;
	HopcroftKarp(int n) :
		adj(n), par(n, -1),
		lv(n), work(n),
		check(n), sz(n) {}
	void AddEdge(int a, int b) { adj[a].push_back(b); }
	void BFS() {
		queue<int> Q;
		for (int i = 0; i < sz; i++) check[i] ? lv[i] = INF : (Q.push(i), lv[i] = 0);
		while (!Q.empty()) {
			auto cur = Q.front(); Q.pop();
			for (auto nxt : adj[cur]) {
				if (par[nxt] != -1 && lv[par[nxt]] == INF)
					lv[par[nxt]] = lv[cur] + 1, Q.push(par[nxt]);
			}
		}
	}
	bool DFS(int cur) {
		for (int& i = work[cur]; i < adj[cur].size(); i++) {
			int nxt = adj[cur][i];
			if (par[nxt] == -1 || lv[par[nxt]] == lv[cur] + 1 && DFS(par[nxt]))
				return check[cur] = 1, par[nxt] = cur, 1;
		}
		return 0;
	}
	int Match() {
		int ret = 0;
		for (int fl = 0; ; fl = 0) {
			fill(work.begin(), work.end(), 0); BFS();
			for (int i = 0; i < sz; i++) if (!check[i] && DFS(i)) fl++;
			if (!fl) break; ret += fl;
		}
		return ret;
	}
};

int main() {
	fastio;
	int n, m; cin >> n >> m;
	HopcroftKarp Flow(n << 1);
	while (m--) {
		int a, b; cin >> a >> b; --a, --b;
		Flow.AddEdge(a, b + n);
	}
	cout << n - Flow.Match() << '\n';
}