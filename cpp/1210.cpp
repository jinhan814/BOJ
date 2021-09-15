#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

struct Dinic { //Dinic algorithm, O(V^2E). O(Esqrt(V)) for Bipartite-Graph.
	struct Edge {
		int nxt;
		int inv; /* inverse edge index */
		int res; /* residual */
	};
	vector<vector<Edge>> adj;
	vector<int> lv, work, check;
	int s, e; //source, sink
	Dinic(int sz) :
		adj(sz), lv(sz), work(sz), check(sz),
		s(-1), e(-1) {
	}
	void set_source(int t) { s = t; }
	void set_sink(int t) { e = t; }
	void add_edge(int a, int b, int cap, bool directed = 1) {
		Edge forward{ b, adj[b].size(), cap };
		Edge reverse{ a, adj[a].size(), directed ? 0 : cap };
		adj[a].push_back(forward);
		adj[b].push_back(reverse);
	}
	bool bfs() {
		memset(&lv[0], -1, sizeof(lv[0]) * lv.size());
		queue<int> Q; lv[s] = 0; Q.push(s);
		while (!Q.empty()) {
			auto cur = Q.front(); Q.pop();
			for (const auto& [nxt, inv, res] : adj[cur]) {
				if (lv[nxt] == -1 && res > 0) {
					lv[nxt] = lv[cur] + 1;
					Q.push(nxt);
				}
			}
		}
		return lv[e] != -1;
	}
	int dfs(int cur, int tot) {
		if (cur == e) return tot;
		for (int& i = work[cur]; i < adj[cur].size(); i++) {
			auto& [nxt, inv, res] = adj[cur][i];
			if (lv[nxt] == lv[cur] + 1 && res > 0) {
				int fl = dfs(nxt, min(tot, res));
				if (fl > 0) {
					res -= fl;
					adj[nxt][inv].res += fl;
					return fl;
				}
			}
		}
		return 0;
	}
	int max_flow() {
		if (s == -1 || e == -1) return -1;
		int ret = 0, fl;
		while (bfs()) {
			memset(&work[0], 0, sizeof(work[0]) * work.size());
			while (fl = dfs(s, INF)) ret += fl;
		}
		return ret;
	}
};

int n, m, st, en;
Dinic flow(402);
bitset<402> visited;

int main() {
	fastio;
	cin >> n >> m >> st >> en;
	flow.set_source(st << 1), flow.set_sink(en << 1 | 1);
	for (int i = 1; i <= n; i++) {
		int t; cin >> t;
		flow.add_edge(i << 1, i << 1 | 1, t);
	}
	while (m--) {
		int a, b; cin >> a >> b;
		flow.add_edge(a << 1 | 1, b << 1, INF);
		flow.add_edge(b << 1 | 1, a << 1, INF);
	}
	flow.max_flow();

	queue<int> Q;
	Q.push(st << 1), visited[st << 1] = 1;
	while (Q.size()) {
		auto cur = Q.front(); Q.pop();
		for (const auto& [nxt, _, res] : flow.adj[cur]) {
			if (visited[nxt] || res <= 0) continue;
			Q.push(nxt), visited[nxt] = 1;
		}
	}

	for (int i = 1; i <= n; i++)
		if (visited[i << 1] && !visited[i << 1 | 1]) cout << i << ' ';
	cout << '\n';
}