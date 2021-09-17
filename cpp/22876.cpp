#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define all(v) (v).begin(), (v).end()
#define compress(v) sort(all(v)), (v).erase(unique(all(v)), (v).end())
#define IDX(v, x) (lower_bound(all(v), x) - (v).begin() + 1)

using pii = pair<int, int>;
using tii = tuple<int, int, int>;

template<typename T = int64_t, size_t sz = 17, typename F = plus<T>>
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

struct Node {
	int x, y;
	Node(int x = 0, int y = 0) : x(x), y(y) {}
	Node operator+ (const Node& rhs) const {
		int v[4]{ x, y, rhs.x, rhs.y };
		sort(v, v + 4);
		return Node(v[2], v[3]);
	}
};

int main() {
	fastio;
	int n; cin >> n;
	vector<tii> v; vector<int> I;
	for (int i = 0; i < n; i++) {
		int a, b, c; cin >> a >> b >> c;
		v.push_back({ a, b, c });
		I.push_back(a); I.push_back(b);
	}

	compress(I);
	for (auto& [a, b, c] : v) a = IDX(I, a), b = IDX(I, b);

	auto Sol_same_dir = [&](bool flag) -> int {
		vector<int> t(I.size() + 1 + 10);
		for (const auto& [a, b, c] : v) t[flag ? a : b] += c;
		sort(t.rbegin(), t.rend());
		return t[0] + t[1] + t[2];
	};

	auto Sol_diff_dir = [&](bool flag) -> int {
		SegTree<Node, 20> ST;
		vector<int> t(I.size() + 1);
		for (const auto& [a, b, c] : v) t[flag ? a : b] += c;
		for (int i = 1; i <= I.size(); i++) ST.Update(i, { 0, t[i] });

		sort(v.begin(), v.end(), [&flag](const tii& a, const tii& b) -> bool {
			return flag ? get<1>(a) < get<1>(b) : get<0>(a) < get<0>(b);
		});

		int ret = 0;
		for (int i = 0, j = 0; i < v.size(); j = i = j + 1) {
			for (; j + 1 < v.size(); j++) {
				if (flag ? get<1>(v[i]) != get<1>(v[j + 1]) :
						   get<0>(v[i]) != get<0>(v[j + 1])) break;
			}
			int cur = 0;
			for (int k = i; k <= j; k++) {
				const auto& [a, b, c] = v[k]; cur += c;
				ST.Update(flag ? a : b, { 0, t[flag ? a : b] -= c });
			}
			auto [x, y] = ST.Query(1, I.size());
			ret = max(ret, cur + x + y);
			for (int k = i; k <= j; k++) {
				const auto& [a, b, c] = v[k];
				ST.Update(flag ? a : b, { 0, t[flag ? a : b] += c });
			}
		}
		return ret;
	};

	cout << [&]() -> int {
		int ret = 0;
		ret = max(ret, Sol_same_dir(0));
		ret = max(ret, Sol_same_dir(1));
		ret = max(ret, Sol_diff_dir(0));
		ret = max(ret, Sol_diff_dir(1));
		return ret;
	}() << '\n';
}