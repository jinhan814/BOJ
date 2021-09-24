#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define all(v) (v).begin(), (v).end()
#define compress(v) sort(all(v)), (v).erase(unique(all(v)), (v).end())
#define IDX(v, x) (lower_bound(all(v), x) - (v).begin())

using pii = pair<int, int>;

template<size_t sz>
struct SegTree {
	vector<pii> tree;
	SegTree() : tree(sz << 1, { -1, -1 }) {}
	void Update(int i, int val) {
		i |= sz; tree[i] = { val, i ^ sz };
		while (i >>= 1) {
			tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
		}
	}
	int Query(int l, int r) {
		pii ret{ -1, -1 };
		l |= sz, r |= sz;
		while (l <= r) {
			if (l & 1) ret = max(ret, tree[l++]);
			if (~r & 1) ret = max(ret, tree[r--]);
			l >>= 1, r >>= 1;
		}
		return ret.second;
	}
	int& operator[] (int i) {
		return tree[i | sz].first;
	}
};

SegTree<1 << 17> ST;

int main() {
	fastio;
	int n; cin >> n;
	vector<pii> v(n); vector<int> I, prv(n, -1), conv(n, -1);
	for (auto& [a, b] : v) cin >> a >> b, I.push_back(b);
	sort(v.begin(), v.end(), [](const pii& a, const pii& b) {
		return a.first ^ b.first ? a.first > b.first : a.second < b.second;
	});

	compress(I);
	for (auto& [a, b] : v) b = IDX(I, b);
	for (int i = 0; i < n; i++) {
		const auto& [a, b] = v[i];
		const int idx = ST.Query(0, b);
		if (idx == -1) ST.Update(b, 1);
		else ST.Update(b, ST[idx] + 1), prv[i] = conv[idx];
		conv[b] = i;
	}

	const int y = ST.Query(0, n - 1);
	cout << ST[y] << '\n';
	for (int i = conv[y]; i != -1; i = prv[i]) {
		cout << v[i].first << ' ' << I[v[i].second] << '\n';
	}
}