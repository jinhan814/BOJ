#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

template<typename T = int, size_t sz = 17, typename F = plus<T>>
struct SegTree {
	vector<T> tree; T t; F f{};
	SegTree(T t = T()) : tree(1 << sz + 1, t), t(t) {}
	explicit SegTree(T t, const F& f) : tree(1 << sz + 1, t), t(t), f(f) {}

	void Update(int i, T val) {
		--i |= 1 << sz; tree[i] = val;
		while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
	}
	T Query(int l, int r) {
		T L = t, R = t; --l |= 1 << sz, --r |= 1 << sz;
		while (l <= r) {
			if (l & 1) L = f(L, tree[l++]);
			if (~r & 1) R = f(tree[r--], R);
			l >>= 1, r >>= 1;
		}
		return f(L, R);
	}
};

template<typename T>
struct _max {
	T operator() (const T& a, const T& b) const {
		return max(a, b);
	}
};

using pii = pair<int, int>;
SegTree<int, 17, plus<int>> ST1;
SegTree<int, 17, _max<int>> ST2;

int GetDist(const pii& a, const pii& b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int GetProfit(const pii& a, const pii& b, const pii& c) {
	return GetDist(a, b) + GetDist(b, c) - GetDist(a, c);
}

int main() {
	fastio;
	int n, q; cin >> n >> q;
	vector<pii> v(n + 1);
	for (int i = 1; i <= n; i++) {
		auto& [a, b] = v[i]; cin >> a >> b;
	}

	for (int i = 2; i <= n; i++) {
		ST1.Update(i, GetDist(v[i - 1], v[i]));
	}
	for (int i = 2; i < n; i++) {
		ST2.Update(i, GetProfit(v[i - 1], v[i], v[i + 1]));
	}

	while (q--) {
		char t; int a, b, c; cin >> t >> a >> b;
		if (t == 'U') {
			cin >> c; v[a] = { b, c };
			if (a > 1) ST1.Update(a, GetDist(v[a - 1], v[a]));
			if (a < n) ST1.Update(a + 1, GetDist(v[a], v[a + 1]));
			for (int i = a - 1; i <= a + 1; i++) {
				if (1 < i && i < n) ST2.Update(i, GetProfit(v[i - 1], v[i], v[i + 1]));
			}
		}
		else {
			cout << ST1.Query(a + 1, b) - ST2.Query(a + 1, b - 1) << '\n';
		}
	}
}