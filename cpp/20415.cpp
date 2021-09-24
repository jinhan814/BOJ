#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

template<typename T>
struct _max { T operator() (const T& a, const T& b) const { return a > b ? a : b; } };

template<typename T = int64_t, size_t sz = 17, typename F = plus<T>>
struct SegTree {
	vector<T> tree; T t; F f{};
	SegTree(T t = T()) : tree(1 << sz + 1, t), t(t) {}
	explicit SegTree(T t, const F& f) : tree(1 << sz + 1, t), t(t), f(f) {}

	void Update(int i, T val) {
		i |= 1 << sz; tree[i] = val;
		while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
	}
	T Query(int l, int r) {
		T L = t, R = t; l |= 1 << sz, r |= 1 << sz;
		while (l <= r) {
			if (l & 1) L = f(L, tree[l++]);
			if (~r & 1) R = f(tree[r--], R);
			l >>= 1, r >>= 1;
		}
		return f(L, R);
	}
};

int n, v[6], conv[128]; string s;
SegTree<int, 16, _max<int>> ST(-INF), nxt(-INF);
constexpr void Init() { for (int i = 0; i < 5; i++) conv["BSGPD"[i]] = i; }

int main() {
	fastio;
	cin >> n;
	for (int i = 1; i <= 4; i++) cin >> v[i]; v[5] = n * v[4] + 1;
	cin >> s;

	Init(); ST.Update(0, 0);
	for (const auto& c : s) {
		const int l = v[conv[c]], r = v[conv[c] + 1];
		for (int i = 0; i <= v[4]; i++) {
			const int mx = ST.Query(max(l - i, 0), min(r - i - 1, v[4]));
			nxt.Update(i, mx + i);
		}
		ST.tree.swap(nxt.tree);
	}
	cout << ST.Query(0, v[4]) << '\n';
}