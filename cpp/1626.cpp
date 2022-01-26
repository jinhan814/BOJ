#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

template<typename T, typename F>
struct SegTree {
	const size_t sz; const T ID; F f;
	vector<T> tree;
	SegTree(size_t n, T ID = T{}) : SegTree(n, ID, F{}) {}
	explicit SegTree(size_t n, T ID, const F& f) :
		sz(Log2(n)), ID(ID), f(f),
		tree(sz << 1, ID) {}
	static size_t Log2(size_t n) {
		n--;
		for (int i = 0; i < 5; i++) n |= n >> (1 << i);
		return n + 1;
	}
	void Update(int i, T val) {
		--i |= sz; tree[i] = val;
		while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
	}
	T Query(int l, int r) const {
		T L = ID, R = ID; --l |= sz, --r |= sz;
		while (l <= r) {
			if (l & 1) L = f(L, tree[l++]);
			if (~r & 1) R = f(tree[r--], R);
			l >>= 1, r >>= 1;
		}
		return f(L, R);
	}
};

struct SegTreeNode {
	int mx, smx;
	SegTreeNode() : SegTreeNode(-INF, -INF) {}
	SegTreeNode(int mx) : SegTreeNode(mx, -INF) {}
	explicit SegTreeNode(int mx, int smx) : mx(mx), smx(smx) {}
};

struct SegTreeMerge {
	using T = SegTreeNode;
	const T operator() (const T& a, const T& b) const {
		T ret; ret.mx = max(a.mx, b.mx);
		if (ret.mx != a.mx && ret.smx < a.mx) ret.smx = a.mx;
		if (ret.mx != a.smx && ret.smx < a.smx) ret.smx = a.smx;
		if (ret.mx != b.mx && ret.smx < b.mx) ret.smx = b.mx;
		if (ret.mx != b.smx && ret.smx < b.smx) ret.smx = b.smx;
		return ret;
	}
};

struct Edge {
	int a, b, cost;
	bool operator< (const Edge& i) const { return cost < i.cost; }
};

struct UnionFind {
    vector<int> par;
    UnionFind(int n) : par(n, -1) {}
    int Find(int x) { return par[x] < 0 ? x : par[x] = Find(par[x]); }
    void Union(int a, int b) {
        a = Find(a), b = Find(b);
        if (a ^ b) par[a] += par[b], par[b] = a;
    }
};

tuple<vector<Edge>, vector<Edge>, int> MST(const vector<Edge>& E, const int n) {
	vector<Edge> E1, E2; int res = 0;
	UnionFind UF(n);
	for (const auto& e : E) {
		const auto& [a, b, cost] = e;
		if (UF.Find(a) == UF.Find(b)) E2.push_back(e);
		else UF.Union(a, b), E1.push_back(e), res += cost;
	}
	return { E1, E2, res };
}

template<typename T, typename F>
struct PathQueryHLD {
	const T ID; F f;
	vector<vector<pair<int, T>>> inp, adj;
	vector<int> sz, dep, par, top, in;
	SegTree<T, F> ST;
	PathQueryHLD(size_t n, T ID = T{}) : PathQueryHLD(n, ID, F{}) {}
	explicit PathQueryHLD(size_t n, T ID, const F& f) :
		ID(ID), f(f),
		inp(n), adj(n),
		sz(n), dep(n), par(n), top(n), in(n),
		ST(n, ID) {}
	void AddEdge(int a, int b, T cost) {
		inp[a].push_back({ b, cost });
		inp[b].push_back({ a, cost });
	}
	void DFS0(int cur, int prv = -1) {
		for (auto& [nxt, cost] : inp[cur]) {
			if (nxt == prv) continue;
			adj[cur].push_back({ nxt, cost });
			DFS0(nxt, cur);
		}
	}
	int DFS1(int cur) {
		sz[cur] = 1;
		for (int i = 0; i < adj[cur].size(); i++) {
			const auto& [nxt, cost] = adj[cur][i];
			dep[nxt] = dep[cur] + 1;
			par[nxt] = cur;
			sz[cur] += DFS1(nxt);
			if (sz[nxt] > sz[adj[cur][0].first]) swap(adj[cur][0], adj[cur][i]);
		}
		return sz[cur];
	}
	void DFS2(int cur) {
		static int dfs_order = 0;
		in[cur] = ++dfs_order;
		for (const auto& [nxt, cost] : adj[cur]) {
			top[nxt] = (nxt == adj[cur][0].first ? top[cur] : nxt);
			DFS2(nxt);
			ST.Update(in[nxt], cost);
		}
	}
	void Init() { DFS0(0), DFS1(0), DFS2(top[0] = 0); }
	T PathQuery(int a, int b) const {
		T ret = ID;
		for (; top[a] ^ top[b]; a = par[top[a]]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			ret = f(ret, ST.Query(in[top[a]], in[a]));
		}
		if (dep[a] > dep[b]) swap(a, b);
		ret = f(ret, ST.Query(in[a] + 1, in[b]));
		return ret;
	}
};

int main() {
	fastio;
	// 1. find mst
	int n, m; cin >> n >> m;
	vector<Edge> E(m);
	for (auto& [a, b, cost] : E) cin >> a >> b >> cost, --a, --b;
	sort(E.begin(), E.end());
	auto [E1, E2, res] = MST(E, n);
	if (E1.size() != n - 1) return !(cout << -1 << '\n');

	// 2. init HLD
	PathQueryHLD<SegTreeNode, SegTreeMerge> HLD(n);
	for (const auto& [a, b, cost] : E1) HLD.AddEdge(a, b, cost);
	HLD.Init();

	// 3. check E2
	int mn = INF;
	for (const auto& [a, b, cost] : E2) {
		auto res = HLD.PathQuery(a, b);
		if (res.mx != cost) mn = min(mn, cost - res.mx);
		else mn = min(mn, cost - res.smx);
	}
	if (mn == INF) cout << -1 << '\n';
	else cout << res + mn << '\n';
}