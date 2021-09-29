#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

template<typename T>
struct _max {
	T operator() (const T& a, const T& b) const {
		return a > b ? a : b;
	}
};

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

int main() {
	fastio;
	int x, y, n; cin >> x >> y >> n;
	vector<pii> v; vector<int> I;
	while (n--) {
		int a, b; cin >> a >> b;
		if (a > x || b > y) continue;
		v.push_back({ a, b });
		I.push_back(a);
	}

	sort(I.begin(), I.end());
	I.erase(unique(I.begin(), I.end()), I.end());
	for (auto& [a, b] : v) a = lower_bound(I.begin(), I.end(), a) - I.begin();
	sort(v.begin(), v.end(), [](const pii& a, const pii& b) {
		return a.second ^ b.second ? a.second > b.second : a.first > b.first;
	});

	SegTree<int, 17, _max<int>> ST;
	for (const auto& [a, b] : v) {
		const int DP = ST.Query(a, I.size() - 1) + 1;
		ST.Update(a, DP);
	}
	cout << ST.Query(0, I.size() - 1) << '\n';
}