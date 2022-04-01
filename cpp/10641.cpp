#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;
using i64 = long long;

template<size_t sz>
struct SegTree {
	vector<i64> tree;
    vector<int> lazy, w;
	SegTree() : tree(sz << 1), lazy(sz << 1), w(sz << 1) {}
	void Init(const vector<int>& I) {
		for (int i = 0; i + 1 < I.size(); i++) w[i | sz] = I[i + 1] - I[i];
		for (int i = sz - 1; i; i--) w[i] = w[i << 1] + w[i << 1 | 1];
	}
	void Clear() {
        memset(&tree[0], 0, sz << 4);
        memset(&lazy[0], 0, sz << 3);
	}
	void Push(int node, int L, int R) {
		if (node < sz) for (const int nxt : { node << 1, node << 1 | 1}) lazy[nxt] += lazy[node];
		tree[node] += (i64)lazy[node] * w[node], lazy[node] = 0;
	}
	void Update(int l, int r, int val, int node = 1, int L = 1, int R = sz) {
		Push(node, L, R);
		if (r < L || R < l) return;
		if (l <= L && R <= r) { lazy[node] += val, Push(node, L, R); return; }
		int mid = L + R >> 1;
		Update(l, r, val, node << 1, L, mid);
		Update(l, r, val, node << 1 | 1, mid + 1, R);
		tree[node] = tree[node << 1] + tree[node << 1 | 1];
	}
	i64 Query(int l, int r, int node = 1, int L = 1, int R = sz) {
		Push(node, L, R);
		if (r < L || R < l) return 0;
		if (l <= L && R <= r) return tree[node];
		int mid = L + R >> 1;
		return Query(l, r, node << 1, L, mid) + Query(l, r, node << 1 | 1, mid + 1, R);
	}
};

template<typename T> struct Info {
	int l, r; T x;
	bool operator< (const Info& i) const { return x < i.x; }
};

int n, m, q, lo[100'001], hi[100'001];
Info<int> O[100'002];
Info<i64> Q[100'001];
SegTree<1 << 19> ST;

void PBS() {
	for (int i = 1; i <= q; i++) hi[i] = 1e9;
	while (1) {
		vector<pii> I;
		for (int i = 1; i <= q; i++) if (lo[i] + 1 < hi[i]) I.push_back({ lo[i] + hi[i] >> 1, i });
		if (I.empty()) break;
		sort(I.begin(), I.end()); ST.Clear();
		for (int i = 1, j = 0; i <= m + 1 && j < I.size(); i++) {
			const auto [l, r, x] = O[i];
			while (j < I.size() && (I[j].first < x || i > m)) {
				const auto [mid, idx] = I[j++];
				if (ST.Query(Q[idx].l, Q[idx].r) < Q[idx].x) lo[idx] = mid;
				else hi[idx] = mid;
			}
			if (i <= m) ST.Update(l, r, 1);
		}
	}
}

int main() {
	fastio;
	// 1. input
	cin >> n >> m >> q;
	vector<int> I; I.reserve(m + q << 1);
	for (int i = 1; i <= m; i++) {
		cin >> O[i].l >> O[i].r >> O[i].x;
		I.push_back(O[i].l);
		I.push_back(O[i].r + 1);
	}
	for (int i = 1; i <= q; i++) {
		cin >> Q[i].l >> Q[i].r >> Q[i].x;
		I.push_back(Q[i].l);
		I.push_back(Q[i].r + 1);
	}

	// 2. Init SegTree, Coordinate Compression
	sort(I.begin(), I.end()); I.erase(unique(I.begin(), I.end()), I.end());
	for (int i = 1; i <= m; i++) {
		O[i].l = lower_bound(I.begin(), I.end(), O[i].l) - I.begin() + 1;
		O[i].r = lower_bound(I.begin(), I.end(), O[i].r + 1) - I.begin();
	}
	for (int i = 1; i <= q; i++) {
		Q[i].l = lower_bound(I.begin(), I.end(), Q[i].l) - I.begin() + 1;
		Q[i].r = lower_bound(I.begin(), I.end(), Q[i].r + 1) - I.begin();
	}
	ST.Init(I); I.clear();

	// 3. PBS
	sort(O + 1, O + m + 1); PBS();
	for (int i = 1; i <= q; i++) cout << hi[i] << '\n';
}