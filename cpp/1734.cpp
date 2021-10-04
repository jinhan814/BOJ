#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct BCC { // vertex-disjoint BCC
	int n, dfs_cnt, color_cnt, art_point_cnt;
	vector<int> dfs_order, low, check;
	vector<vector<int>> adj, v, color;

	BCC(int n) :
		n(n), adj(n + 1), v(n + 1),
		dfs_order(n + 1), low(n + 1),
		check(n + 1), color(n + 1),
		dfs_cnt(0), color_cnt(0), art_point_cnt(0) {}

	void AddEdge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	int DFS(int cur, bool IsRoot = 0) {
		int& ret = low[cur] = dfs_order[cur] = ++dfs_cnt, cnt = 0;
		for (const auto& nxt : adj[cur]) {
			if (!dfs_order[nxt]) {
				const int t = DFS(nxt);
				if (t >= dfs_order[cur] && !IsRoot && !check[cur])
					check[cur] = ++art_point_cnt;
				ret = min(ret, t), cnt++;
			}
			else ret = min(ret, dfs_order[nxt]);
		}
		if (IsRoot) check[cur] = cnt > 1 ? ++art_point_cnt : 0;
		return ret;
	}

	void Color(int cur, int p = 0) {
		if (p) { // cur != root
			color[p].push_back(cur);
			v[cur].push_back(p);
		}
		for (const auto& nxt : adj[cur]) {
			if (v[nxt].size()) continue;
			if (low[nxt] >= dfs_order[cur]) {
				color[++color_cnt].push_back(cur);
				v[cur].push_back(color_cnt);
				Color(nxt, color_cnt);
			}
			else Color(nxt, p);
		}
	}

	void Construct(bool flag = 0) { // suppose that graph is connected, no self-loop and multi-edge, V >= 2
		DFS(1, 1); Color(1, 0);

		if (flag) {
			cout << '\n' << "articulation-point :" << '\n';
			cout << art_point_cnt << '\n';
			for (int i = 1; i <= n; i++) if (check[i]) cout << i << ' ';
			cout << "\n\n";

			cout << "color :" << '\n';
			for (int i = 1; i <= color_cnt; i++) {
				for (const auto& j : color[i]) cout << j << ' ';
				cout << '\n';
			}
		}
	}
};

struct BlockCutTree {
	int n;
	vector<vector<int>> adj;

	BlockCutTree(const BCC& B) :
		n(B.color_cnt + B.art_point_cnt),
		adj(n + 1) { Construct(B); }

	void AddEdge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	void Construct(const BCC& B) {
		for (int i = 1; i <= B.n; i++) {
			if (!B.check[i]) continue;
			for (const auto& color : B.v[i])
				AddEdge(color, B.check[i] + B.color_cnt);
		}
	}
};

struct HLD {
	vector<int> sz, dep, par, top;
	vector<vector<int>> inp, adj;

	HLD(int n) :
		sz(n + 1), dep(n + 1),
		par(n + 1), top(n + 1),
		inp(n + 1), adj(n + 1) {}

	void AddEdge(int a, int b) {
		inp[a].push_back(b);
		inp[b].push_back(a);
	}

	void DFS(int cur = 1, int prev = -1) {
		for (auto nxt : inp[cur]) {
			if (nxt == prev) continue;
			adj[cur].push_back(nxt);
			DFS(nxt, cur);
		}
	}

	void DFS1(int cur = 1) {
		sz[cur] = 1;
		for (auto& nxt : adj[cur]) {
			dep[nxt] = dep[cur] + 1; par[nxt] = cur;
			DFS1(nxt); sz[cur] += sz[nxt];
			if (sz[nxt] > sz[adj[cur][0]]) swap(nxt, adj[cur][0]);
		}
	}

	void DFS2(int cur = 1) {
		for (auto nxt : adj[cur]) {
			top[nxt] = (nxt == adj[cur][0] ? top[cur] : nxt);
			DFS2(nxt);
		}
	}

	void Construct() {
		DFS(); DFS1();
		DFS2(top[1] = 1);
	}

	int LCA(int a, int b) {
		for (; top[a] ^ top[b]; a = par[top[a]])
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
		if (dep[a] > dep[b]) swap(a, b);
		return a;
	}

	bool IsPath(int a, int b, int c) {
		const int lca = LCA(a, b);
		if (lca == c) return 1;
		if (LCA(lca, c) == c) return 0;
		return LCA(a, c) == c || LCA(b, c) == c;
	}
};

int main() {
	fastio;
	int n, m; cin >> n >> m;
	BCC Graph(n);
	while (m--) {
		int a, b; cin >> a >> b;
		Graph.AddEdge(a, b);
	}
	Graph.Construct();

	BlockCutTree T(Graph); HLD H(T.n);
	for (int i = 1; i <= T.n; i++) for (const auto& j : T.adj[i])
		if (i < j) H.AddEdge(i, j);
	H.Construct();

	vector<tuple<int, int, int>> bridge;
	for (int i = 1; i <= Graph.color_cnt; i++) {
		if (Graph.color[i].size() != 2) continue;
		int a = Graph.color[i][0], b = Graph.color[i][1];
		if (a > b) swap(a, b);
		bridge.push_back({ a, b, i });
	}
	sort(bridge.begin(), bridge.end());

	int q; cin >> q;
	while (q--) {
		int t, a, b, c, d; cin >> t;
		if (t & 1) {
			cin >> a >> b >> c >> d;
			if (a > b) swap(a, b);
			if (c > d) swap(c, d);
			auto it = lower_bound(bridge.begin(), bridge.end(), tuple<int, int, int>{ c, d, -1e9 });
			if (it != bridge.end() && get<0>(*it) == c && get<1>(*it) == d) {
				const int bridge_idx = get<2>(*it);
				const int a_idx = Graph.check[a] ? Graph.check[a] + Graph.color_cnt : Graph.v[a][0];
				const int b_idx = Graph.check[b] ? Graph.check[b] + Graph.color_cnt : Graph.v[b][0];
				cout << (H.IsPath(a_idx, b_idx, bridge_idx) ? "no" : "yes") << '\n';
			}
			else cout << "yes" << '\n';
		}
		else {
			cin >> a >> b >> c;
			if (a > b) swap(a, b);
			if (Graph.check[c]) {
				const int a_idx = Graph.check[a] ? Graph.check[a] + Graph.color_cnt : Graph.v[a][0];
				const int b_idx = Graph.check[b] ? Graph.check[b] + Graph.color_cnt : Graph.v[b][0];
				const int c_idx = Graph.check[c] + Graph.color_cnt;
				cout << (H.IsPath(a_idx, b_idx, c_idx) ? "no" : "yes") << '\n';
			}
			else cout << "yes" << '\n';
		}
	}
}