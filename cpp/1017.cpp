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

template<size_t sz = 10'000>
struct LinearSieve {
	vector<int> p;
	int sieve[sz + 1]; // sieve[i] : IsPrime(i) ? 0 : smallest prime factor
	LinearSieve() : sieve{} {
		for (int i = 2; i <= sz; i++) {
			if (!sieve[i]) p.push_back(i);
			for (auto j : p) {
				if (i * j > sz) break;
				sieve[i * j] = j;
				if (i % j == 0) break;
			}
		}
	}
}; LinearSieve Sieve;

int main() {
	fastio;
	int n; cin >> n;
	vector<int> v(n), l, r, ans;
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		(v[i] & 1 ? l : r).push_back(v[i]);
	}
	if (l.size() != r.size()) return !(cout << -1 << '\n');
	if (v[0] & 1) l.erase(find(l.begin(), l.end(), v[0]));
	else r.erase(find(r.begin(), r.end(), v[0]));

	auto& cur = v[0] & 1 ? r : l;
	for (int _ = 0; _ < n / 2; _++) {
		const int t = cur[0]; cur.erase(cur.begin());
		if (!Sieve.sieve[v[0] + t]) {
			HopcroftKarp flow(2 * n - 2);
			for (int i = 0; i < n / 2 - 1; i++) for (int j = 0; j < n / 2 - 1; j++) {
				if (!Sieve.sieve[l[i] + r[j]]) flow.AddEdge(i, n / 2 - 1 + j);
			}
			if (flow.Match() == n / 2 - 1) ans.push_back(t);
		}
		cur.push_back(t);
	}

	if (ans.empty()) return !(cout << -1 << '\n');
	sort(ans.begin(), ans.end());
	for (auto& i : ans) cout << i << ' '; cout << '\n';
}