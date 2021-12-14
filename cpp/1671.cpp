#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

struct Dinic { // Dinic algorithm, O(V^2E). O(Esqrt(V)) for Bipartite-Graph.
	struct Edge { int nxt, inv, res; };
	vector<vector<Edge>> adj;
	vector<int> lv, work, check;
	int s, e; //source, sink
	Dinic(int sz) : adj(sz), lv(sz), work(sz), check(sz), s(-1), e(-1) {}
	void SetSource(int t) { s = t; }
	void SetSink(int t) { e = t; }
	void AddEdge(int a, int b, int cap, bool directed = 1) {
		Edge forward{ b, adj[b].size(), cap };
		Edge reverse{ a, adj[a].size(), directed ? 0 : cap };
		adj[a].push_back(forward);
		adj[b].push_back(reverse);
	}
	bool BFS() {
		memset(&lv[0], -1, sizeof(lv[0]) * lv.size());
		queue<int> Q; lv[s] = 0; Q.push(s);
		while (!Q.empty()) {
			auto cur = Q.front(); Q.pop();
			for (const auto& [nxt, inv, res] : adj[cur]) {
				if (lv[nxt] == -1 && res > 0)
					lv[nxt] = lv[cur] + 1, Q.push(nxt);
			}
		}
		return lv[e] != -1;
	}
	int DFS(int cur, int tot) {
		if (cur == e) return tot;
		for (int& i = work[cur]; i < adj[cur].size(); i++) {
			auto& [nxt, inv, res] = adj[cur][i];
			if (lv[nxt] == lv[cur] + 1 && res > 0) {
				int fl = DFS(nxt, min(tot, res));
				if (fl > 0) return res -= fl, adj[nxt][inv].res += fl, fl;
			}
		}
		return 0;
	}
	int MaxFlow() {
		if (s == -1 || e == -1) return -1;
		int ret = 0, fl;
		while (BFS()) {
			memset(&work[0], 0, sizeof(work[0]) * work.size());
			while (fl = DFS(s, INF)) ret += fl;
		}
		return ret;
	}
};

int n, v[50][3];
Dinic Flow(102);

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1] >> v[i][2];
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (i ^ j) {
		if (v[i][0] == v[j][0] && v[i][1] == v[j][1] && v[i][2] == v[j][2])
			i < j ? Flow.AddEdge(i + 1, j + n + 1, 1) : void();
		else if (v[i][0] >= v[j][0] && v[i][1] >= v[j][1] && v[i][2] >= v[j][2])
			Flow.AddEdge(i + 1, j + n + 1, 1);
	}
	for (int i = 0; i < n; i++) {
		Flow.AddEdge(0, i + 1, 2);
		Flow.AddEdge(i + n + 1, 2 * n + 1, 1);
	}
	Flow.SetSource(0), Flow.SetSink(2 * n + 1);
	cout << n - Flow.MaxFlow() << '\n';
}