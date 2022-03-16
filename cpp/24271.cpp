#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

template<size_t sz>
struct SegTree {
	int tree[sz << 1];
	void Init() {
		for (int i = sz; --i;) tree[i] = tree[i << 1] ^ tree[i << 1 | 1];
	}
	void Update(int i, int val) {
		tree[i |= sz] ^= val;
		while (i >>= 1) tree[i] = tree[i << 1] ^ tree[i << 1 | 1];
	}
	int Query(int l, int r, int x, int node, int L, int R) const {
		const int b = R - L + 1;
		if (x & b) node ^= 1;
		if (R < l || r < L) return 0;
		if (l <= L && R <= r) return tree[node];
		const int mid = L + R >> 1;
		return Query(l, r, x, node << 1, L, mid) ^ Query(l, r, x, node << 1 | 1, mid + 1, R);
	}
	int Query(int l, int r, int x) const { return Query(l, r, x, 1, 0, sz - 1); }
};

SegTree<1 << 18> ST;

int main() {
	fastio;
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> ST.tree[i | 1 << 18];
	ST.Init();
	int q; cin >> q;
	while (q--) {
		int t, a, b, c; cin >> t >> a >> b;
		if (t & 1) cin >> c, cout << ST.Query(a, b, c) << '\n';
		else ST.Update(a, b);
	}
}