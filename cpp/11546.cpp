#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define all(v) (v).begin(), (v).end()
#define compress(v) sort(all(v)), (v).erase(unique(all(v)), (v).end())
#define IDX(v, x) lower_bound(all(v), x) - (v).begin() + 1

using Pii = pair<int, int>;
using Info = tuple<int, int, int>;
using Event = tuple<int, int, int>;

template<size_t sz>
struct SegTree {
	vector<int> tree, lazy;
	SegTree() : tree(sz << 1), lazy(sz << 1) {}
	void Push(int node) {
		if (node < sz) for (const int nxt : { node << 1, node << 1 | 1}) lazy[nxt] ^= lazy[node];
		else tree[node] ^= lazy[node];
		lazy[node] = 0;
	}
	void Update(int l, int r, int val, int node = 1, int L = 1, int R = sz) {
		Push(node);
		if (r < L || R < l) return;
		if (l <= L && R <= r) { lazy[node] ^= val, Push(node); return; }
		int mid = L + R >> 1;
		Update(l, r, val, node << 1, L, mid);
		Update(l, r, val, node << 1 | 1, mid + 1, R);
		tree[node] = tree[node << 1] ^ tree[node << 1 | 1];
	}
	int Query(int l, int r, int node = 1, int L = 1, int R = sz) {
		Push(node);
		if (r < L || R < l) return 0;
		if (l <= L && R <= r) return tree[node];
		int mid = L + R >> 1;
		return Query(l, r, node << 1, L, mid) ^ Query(l, r, node << 1 | 1, mid + 1, R);
	}
};

int main() {
	fastio;
	// input
	int n, m; cin >> n >> m;
	vector<Info> v(n); vector<Pii> w(m); vector<int> I;
	for (int i = 0; i < n; i++) {
		auto& [x, y, idx] = v[i];
		cin >> x >> y, idx = i + 1;
		I.push_back(y);
	}
	for (auto& [x, y] : w) cin >> x >> y, I.push_back(y);

	// coordinate compression
	compress(I);
	for (auto& [x, y, idx] : v) y = IDX(I, y);
	for (auto& [x, y] : w) y = IDX(I, y);

	// get Events
	vector<Event> e;
	for (int i = 0; i < m; i++) {
		const auto& [x1, y1] = w[i];
		const auto& [x2, y2] = w[(i + 1) % m];
		if (x1 == x2) e.push_back({ x1, min(y1, y2), max(y1, y2) });
	}

	// sort
	sort(v.begin(), v.end());
	sort(e.begin(), e.end());

	// sweeping
	SegTree<1 << 18> ST; int64_t ans = 0;
	for (int i = 0, j = 0; i < n; i++) {
		const auto& [x, y, idx] = v[i];
		while (j < e.size() && get<0>(e[j]) <= x) {
			const auto& [x, l, r] = e[j++];
			ST.Update(l, r - 1, 1);
		}
		if (!ST.Query(y - 1, y - 1) || !ST.Query(y, y)) ans += idx;
	}
	cout << ans << '\n';
}