#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct BCC { // edge-disjoint bcc
	int n, dfs_cnt, color_cnt;
	vector<int> dfs_order, low, v;
	vector<vector<int>> color;
	vector<tuple<int, int, int>> bridge;
	vector<vector<pair<int, int>>> adj;

	BCC(int n) :
		n(n), adj(n + 1), v(n + 1),
		dfs_order(n + 1), low(n + 1),
		color(n + 1), dfs_cnt(0), color_cnt(0) {}

	void AddEdge(int a, int b, int idx) {
		adj[a].push_back({ b, idx });
		adj[b].push_back({ a, idx });
	}

	void InitDummy() {
		vector<int> visited(n + 1);
		for (int i = 1; i <= n; i++) {
			if (visited[i]) continue;
			queue<int> Q; AddEdge(i, 0, 1e9);
			visited[i] = 1, Q.push(i);
			while (Q.size()) {
				auto cur = Q.front(); Q.pop();
				for (const auto& [nxt, idx] : adj[cur])
					if (!visited[nxt]) visited[nxt] = 1, Q.push(nxt);
			}
		}
	}

	int DFS(int cur, int prv_idx = -1) {
		int& ret = low[cur] = dfs_order[cur] = ++dfs_cnt;
		for (const auto& [nxt, idx] : adj[cur]) {
			if (idx == prv_idx) continue;
			if (!dfs_order[nxt]) {
				const int t = DFS(nxt, idx);
				if (t > dfs_order[cur]) bridge.push_back({ cur, nxt, idx });
				ret = min(ret, t);
			}
			else ret = min(ret, dfs_order[nxt]);
		}
		return ret;
	}

	void Color(int cur, int p) {
		if (p) {
			color[p].push_back(cur);
			v[cur] = p;
		}
		for (const auto& [nxt, idx] : adj[cur]) {
			if (v[nxt] || !nxt) continue;
			if (low[nxt] > dfs_order[cur]) Color(nxt, ++color_cnt);
			else Color(nxt, p);
		}
	}

	void GetBridge(bool flag = 0) {
		InitDummy(); DFS(0); Color(0, 0);
		for (auto& [a, b, idx] : bridge) if (a > b) swap(a, b);
		sort(bridge.begin(), bridge.end());

		if (flag) {
			cout << '\n' << "bridge :" << '\n';
			cout << bridge.size() << '\n';
			for (auto& [a, b, idx] : bridge) cout << a << ' ' << b << '\n';
			cout << '\n';

			cout << "color :" << '\n';
			for (int i = 1; i <= color_cnt; i++) {
				for (const auto& j : color[i]) cout << j << ' ';
				cout << '\n';
			}
			cout << '\n';
		}
	}
};

struct BCCTree { // edge-disjoint bcc tree
	int n;
	vector<vector<int>> adj;

	BCCTree(const BCC& B) :
		n(B.color_cnt),
		adj(n + 1) { Construct(B); }

	void AddEdge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	void Construct(const BCC& B) {
		for (const auto& [a, b, idx] : B.bridge)
			AddEdge(B.v[a], B.v[b]);
	}
};

template<size_t sz>
struct SegTree { // range add update, sum query segment tree
	vector<int> tree, lazy;
	SegTree() : tree(sz << 1), lazy(sz << 1) {}
	void Push(int node, int L, int R) {
		if (node < sz) for (const int nxt : { node << 1, node << 1 | 1}) lazy[nxt] += lazy[node];
		tree[node] += lazy[node] * (R - L + 1), lazy[node] = 0;
	}
	void Update(int l, int r, int val, int node = 1, int L = 1, int R = sz) {
		Push(node, L, R);
		if (r < L || R < l) return;
		if (l <= L && R <= r) { lazy[node] += val, Push(node, L, R); return; }
		int mid = L + R >> 1;
		Update(l, r, val, node << 1, L, mid);
		Update(l, r, val, node << 1 | 1, mid + 1, R);
		tree[node] = tree[node << 1] + tree[node << 1 | 1];
	}
	int Query(int l, int r, int node = 1, int L = 1, int R = sz) {
		Push(node, L, R);
		if (r < L || R < l) return 0;
		if (l <= L && R <= r) return tree[node];
		int mid = L + R >> 1;
		return Query(l, r, node << 1, L, mid) + Query(l, r, node << 1 | 1, mid + 1, R);
	}
};

struct HLD {
	SegTree<1 << 17> ST;
	vector<int> sz, dep, par, top, in, out;
	vector<vector<int>> inp, adj;

	HLD(int n) :
		sz(n + 1), dep(n + 1),
		par(n + 1), top(n + 1),
		in(n + 1), out(n + 1),
		inp(n + 1), adj(n + 1) {}

	void AddEdge(int a, int b) {
		inp[a].push_back(b);
		inp[b].push_back(a);
	}

	void DFS(int cur = 1, int prv = -1) {
		for (const auto& nxt : inp[cur]) {
			if (nxt == prv) continue;
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
		static int dfs_order = 0;
		in[cur] = ++dfs_order;
		for (const auto& nxt : adj[cur]) {
			top[nxt] = (nxt == adj[cur][0] ? top[cur] : nxt);
			DFS2(nxt);
		}
		out[cur] = dfs_order;
	}

	void Construct() {
		DFS(), DFS1();
		DFS2(top[1] = 1);
	}

	int LCA(int a, int b) {
		for (; top[a] ^ top[b]; a = par[top[a]]) if (dep[top[a]] < dep[top[b]]) swap(a, b);
		if (dep[a] > dep[b]) swap(a, b);
		return a;
	}

	void Update(int a, int b) {
		const int lca = LCA(a, b);
		for (; top[a] ^ top[lca]; a = par[top[a]]) ST.Update(in[top[a]], in[a], 1);
		ST.Update(in[lca] + 1, in[a], 1);
		for (; top[b] ^ top[lca]; b = par[top[b]]) ST.Update(in[top[b]], in[b], -1);
		ST.Update(in[lca] + 1, in[b], -1);
	}

	int NodeQuery(int x) {
		return ST.Query(in[x], in[x]);
	}
};

int main() {
	fastio;
	int n, m; cin >> n >> m;
	vector<pair<int, int>> edge(m); BCC B(n);
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		edge[i] = { a, b };
		B.AddEdge(a, b, i);
	}
	B.GetBridge();

	BCCTree T(B); HLD H(T.n);
	for (int i = 0; i <= T.n; i++) for (const auto& j : T.adj[i])
		if (i < j) H.AddEdge(i, j);
	H.Construct();

	vector<vector<pair<int, int>>> conv(T.n + 1);
	for (const auto& [a, b, idx] : B.bridge) {
		int t1 = B.v[a], t2 = B.v[b];
		if (t1 > t2) swap(t1, t2);
		conv[t1].push_back({ t2, idx });
	}
	for (int i = 1; i <= T.n; i++) sort(conv[i].begin(), conv[i].end());

	int q; cin >> q;
	for (int i = 0; i < q; i++) {
		int a, b; cin >> a >> b;
		if (B.v[a] == B.v[b]) continue;
		H.Update(B.v[a], B.v[b]);
	}

	string ans(m, 'B');
	for (int i = 1; i <= T.n; i++) for (const auto& j : T.adj[i]) {
		if (i >= j) continue;

		int a = i, b = j;
		if (H.dep[a] < H.dep[b]) swap(a, b);
		const int t = H.NodeQuery(a);

		int pa = a, pb = b;
		if (a > b) swap(a, b);
		const auto it = lower_bound(conv[a].begin(), conv[a].end(), pair<int, int>{ b, -1e9 });
		const int idx = it->second;
		const int flag = B.v[edge[idx].first] == pb;

		if (!t) continue;
		if (flag ^ (t > 0)) ans[idx] = 'R'; // a -> b
		else ans[idx] = 'L'; // b -> a
	}
	cout << ans << '\n';
}