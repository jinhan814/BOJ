#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;

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
	ll v[4];
	Node(ll val = 0) : v{} { v[3] = val; }
	const ll Max() const { return max(max(v[0], v[1]), max(v[2], v[3])); }
};

struct Merge {
	Node operator() (const Node& a, const Node& b) const {
		Node ret;
		for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) {
			if (i & 1 && j & 2) continue;
			ret.v[i & 2 | j & 1] = max(ret.v[i & 2 | j & 1], a.v[i] + b.v[j]);
		}
		return ret;
	}
};

int main() {
	fastio;
	int n, q; cin >> n >> q;
	SegTree<Node, Merge> ST(n);
	for (int i = 1; i <= n; i++) {
		int t; cin >> t;
		ST.Update(i, t);
	}
	ll sum = 0;
	for (int a, b; q-- && cin >> a >> b;) {
		ST.Update(a, b);
		sum += ST.tree[1].Max();
	}
	cout << sum << '\n';
}