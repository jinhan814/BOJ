#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;
using pii = pair<int, int>;

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

pii Conv(const string& s1, const string& s2) {
	int t1 = 0, t2 = 0;
	for (int i = 1; i < s1.size(); i++) t1 = t1 * 10 + (s1[i] & 15);
	for (int i = 1; i < s2.size(); i++) t2 = t2 * 10 + (s2[i] & 15);
	return { t1, t2 };
}

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int a, b, n; cin >> a >> b >> n;
		vector<pii> v, w;
		for (int i = 0; i < n; i++) {
			string s1, s2; cin >> s1 >> s2;
			if (s1[0] == 'C') v.push_back(Conv(s1, s2));
			else w.push_back(Conv(s1, s2));
		}
		HopcroftKarp flow(n);
		for (int i = 0; i < v.size(); i++) for (int j = 0; j < w.size(); j++) {
			if (v[i].first == w[j].second ||
				v[i].second == w[j].first) flow.AddEdge(i, v.size() + j);
		}
		cout << n - flow.Match() << '\n';
	}
}