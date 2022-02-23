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
		i |= sz; tree[i] = val;
		while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
	}
	T Query(int l, int r) const {
		T L = ID, R = ID; l |= sz, r |= sz;
		while (l <= r) {
			if (l & 1) L = f(L, tree[l++]);
			if (~r & 1) R = f(tree[r--], R);
			l >>= 1, r >>= 1;
		}
		return f(L, R);
	}
};

template<typename T> struct Max {
	constexpr T operator() (const T& a, const T& b) const {
		return a > b ? a : b;
	}
};

int n, m, mx;
int par[50'001];
int dfs_cnt, dfs_order[50'001], low[50'001];
vector<int> adj[50'001], v[50'001];

int DFS(int cur, int prv) {
	int& ret = low[cur] = dfs_order[cur] = ++dfs_cnt;
	par[cur] = prv;
	for (const auto& nxt : adj[cur]) {
		if (nxt == prv) continue;
		if (!dfs_order[nxt]) ret = min(ret, DFS(nxt, cur));
		else ret = min(ret, dfs_order[nxt]);
	}
	return ret;
}

int Calc(int idx) {
	int ret = 0, sz = v[idx].size();
	SegTree<int, Max<int>> ST1(sz, -INF);
	SegTree<int, Max<int>> ST2(sz, -INF);
	for (int i = 0; i < sz; i++) {
		ST1.Update(i, v[idx][i] - i);
		ST2.Update(i, v[idx][i] + i);
	}
	for (int i = 0; i < sz; i++) {
		int res = 0;
		if (i - sz / 2 >= 0) {
			res = max(res, ST1.Query(i - sz / 2, i - 1) + i);
		}
		else {
			res = max(res, ST1.Query(0, i - 1) + i);
			res = max(res, ST1.Query(sz - sz / 2 + i, sz - 1) + sz + i);
		}
		if (i + sz / 2 < sz) {
			res = max(res, ST2.Query(i + 1, i + sz / 2) - i);
		}
		else {
			res = max(res, ST2.Query(i + 1, sz - 1) - i);
			res = max(res, ST2.Query(0, sz / 2 - sz + i) + sz - i);
		}
		res += v[idx][i];
		mx = max(mx, res);
		if (i == sz - 1) ret = res;
	}
	v[idx].clear();
	return ret;
}

int Sol(int cur) {
	int ret = 0;
	for (const auto& nxt : adj[cur]) {
		if (par[nxt] != cur);                 // back edge
		else if (low[nxt] < dfs_order[nxt]) { // cycle edge
			v[low[nxt]].push_back(Sol(nxt));
			if (low[nxt] == dfs_order[cur]) {
				v[low[nxt]].push_back(0);
				auto res = Calc(low[nxt]);
				mx = max(mx, ret + res);
				ret = max(ret, res);
			}
		}
		else {                                // tree edge
			auto res = Sol(nxt) + 1;
			mx = max(mx, ret + res);
			ret = max(ret, res);
		}
	}
	return ret;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int t, a, b; m-- && cin >> t >> a;) {
		for (; --t && cin >> b; a = b) {
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
	}
	DFS(1, -1), Sol(1);
	cout << mx << '\n';
}