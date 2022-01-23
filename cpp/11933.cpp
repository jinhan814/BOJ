#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;
using ll = long long;
constexpr ll INF = ll(1e18) + 7;

template<typename T, typename F>
struct SegTree { // 1-based
	const size_t sz; const T ID; F f{};
	vector<T> tree;
	SegTree(size_t n, T ID) : SegTree(n, ID, F{}) {}
	explicit SegTree(size_t n, T ID, const F& f) :
		sz(Log2(n)), ID(ID), f(f),
		tree(sz << 1, ID) {}
	static size_t Log2(size_t n) { // return 2^m >= n
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

struct HLD { // 0-based
	vector<vector<pii>> inp, adj;
	vector<int> sz, dep, par, top, in, out;
	SegTree<ll, plus<ll>> ST;
	HLD(int n) : inp(n), adj(n), sz(n), dep(n), par(n), top(n), in(n), out(n), ST(n, 0) {}
	void AddEdge(int a, int b, int cost) {
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
		out[cur] = dfs_order;
	}
	void Init() { DFS0(0), DFS1(0), DFS2(top[0] = 0); }
	int LCA(int a, int b) const {
		for (; top[a] ^ top[b]; a = par[top[a]]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
		}
		if (dep[a] > dep[b]) swap(a, b);
		return a;
	}
	ll GetDist(int a, int b) const {
		ll ret = 0;
		for (; top[a] ^ top[b]; a = par[top[a]]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			ret += ST.Query(in[top[a]], in[a]);
		}
		if (dep[a] > dep[b]) swap(a, b);
		ret += ST.Query(in[a] + 1, in[b]);
		return ret;
	}
};

vector<pair<int, ll>> adj[500'000];
ll dist[500'000];

ll Dijkstra(const vector<int>& v, const vector<int>& A, const vector<int>& B) { // return min_dist(A, B) on Compressed Tree
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> PQ;
	for (auto& i : v) dist[i] = INF;
	for (auto& i : A) PQ.push({ dist[i] = 0, i });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (const auto& [nxt, cost] : adj[cur]) {
			if (dist[nxt] > dist[cur] + cost)
				PQ.push({ dist[nxt] = dist[cur] + cost, nxt });
		}
	}
	ll ret = INF;
	for (auto& i : B) ret = min(ret, dist[i]);
	return ret;
}

ll Query(const HLD& H, const vector<int>& A, const vector<int>& B) { // return min_dist(A, B) on Main Tree H
	const auto Cmp = [&H](const int a, const int b) -> bool { return H.in[a] < H.in[b]; };
	vector<int> v = A;
	for (auto& i : B) v.push_back(i);
	sort(v.begin(), v.end(), Cmp);

	for (int i = 1, sz = v.size(); i < sz; i++) v.push_back(H.LCA(v[i - 1], v[i]));
	sort(v.begin(), v.end(), Cmp);
	v.erase(unique(v.begin(), v.end()), v.end());

	for (int i = 1; i < v.size(); i++) {
		const auto par = H.LCA(v[i - 1], v[i]);
		const auto dist = H.GetDist(par, v[i]);
		adj[par].push_back({ v[i], dist });
		adj[v[i]].push_back({ par, dist });
	}
	auto ret = Dijkstra(v, A, B);
	for (auto& i : v) adj[i].clear();
	return ret;
}

int main() {
	fastio;
	// 1. Init HLD
	int n, q; cin >> n >> q;
	HLD H(n);
	for (int i = 1; i < n; i++) {
		int a, b, c; cin >> a >> b >> c;
		H.AddEdge(a, b, c);
	}
	H.Init();

	// 2. Query
	while (q--) {
		int a, b; cin >> a >> b;
		vector<int> A(a), B(b);
		for (int i = 0; i < a; i++) cin >> A[i];
		for (int i = 0; i < b; i++) cin >> B[i];
		cout << Query(H, A, B) << '\n';
	}
}