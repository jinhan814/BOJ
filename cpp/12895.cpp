#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using u32 = unsigned int;

template<size_t sz>
struct LazySegTree {
	vector<u32> tree, lazy;
	LazySegTree() : tree(sz << 1, 1), lazy(sz << 1) {}
	void Push(int node) {
		if (!lazy[node]) return;
		if (node < sz) lazy[node << 1] = lazy[node << 1 | 1] = lazy[node];
		tree[node] = lazy[node], lazy[node] = 0;
	}
	void Update(int l, int r, int val, int node = 1, int L = 1, int R = sz) {
		Push(node);
		if (r < L || R < l) return;
		if (l <= L && R <= r) { lazy[node] = 1 << val, Push(node); return; }
		const int mid = L + R >> 1;
		Update(l, r, val, node << 1, L, mid);
		Update(l, r, val, node << 1 | 1, mid + 1, R);
		tree[node] = tree[node << 1] | tree[node << 1 | 1];
	}
	u32 Query(int l, int r, int node = 1, int L = 1, int R = sz) {
		Push(node);
		if (r < L || R < l) return 0;
		if (l <= L && R <= r) return tree[node];
		const int mid = L + R >> 1;
		return Query(l, r, node << 1, L, mid) | Query(l, r, node << 1 | 1, mid + 1, R);
	}
};

LazySegTree<1 << 17> ST;

int main() {
	fastio;
	int n, q; cin >> n >> q >> q;
	while (q--) {
		char c; int l, r, val; cin >> c >> l >> r;
		if (l > r) swap(l, r);
		if (c == 'C') cin >> val, ST.Update(l, r, val - 1);
		else cout << __builtin_popcount(ST.Query(l, r)) << '\n';
	}
}