#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 1e9 + 7;

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

struct Node {
	int v[5][5];
	Node() : v{} {}
};

struct Merge {
	Node operator() (const Node& a, const Node& b) const {
		Node ret;
		for (int l1 = 0; l1 < 5; l1++) for (int r1 = l1; r1 < 5; r1++) {
			ret.v[l1][r1] += a.v[l1][r1];
			if (ret.v[l1][r1] >= MOD) ret.v[l1][r1] -= MOD;
			ret.v[l1][r1] += b.v[l1][r1];
			if (ret.v[l1][r1] >= MOD) ret.v[l1][r1] -= MOD;
			for (int r2 = r1 + 1; r2 < 5; r2++) {
				ret.v[l1][r2] += (1LL * a.v[l1][r1] * b.v[r1 + 1][r2]) % MOD;
				if (ret.v[l1][r2] >= MOD) ret.v[l1][r2] -= MOD;
			}
		}
		return ret;
	}
};

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n, m, q; cin >> n >> m >> q;
		string a, b; cin >> a >> b;
		SegTree<Node, Merge> ST(n, Node{});
		auto Update = [&](int i, char c) {
			Node cur;
			for (int i = 0; i < m; i++) if (c == b[i]) cur.v[i][i] = 1;
			ST.Update(i, cur);
		};
		for (int i = 0; i < n; i++) Update(i + 1, a[i]);
		cout << ST.tree[1].v[0][m - 1] << '\n';
		while (q--) {
			int l, r; string s; cin >> l >> r >> s;
			for (int i = 0; i < s.size(); i++) Update(l + i, s[i]);
			cout << ST.tree[1].v[0][m - 1] << '\n';
		}
	}
}