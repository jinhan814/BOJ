#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;
using pii = pair<int, int>;

struct Query { int l, r, x; };

struct Fenwick {
	ll tree[300'001];
	void Init() { memset(tree, 0, sizeof tree); }
	void Update(int i, int x) {
		for (; i <= 300'000; i += i & -i) tree[i] += x;
	}
	void Update(int l, int r, int x) {
		if (l <= r) Update(l, x), Update(r + 1, -x);
		else Update(l, x), Update(1, x), Update(r + 1, -x);
	}
	ll Query(int i) {
		ll ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
} FT;

int n, m, q, v[300'001], lo[300'001], hi[300'001];
Query Q[300'001];
vector<int> pos[300'001];

void PBS() {
	for (int i = 1; i <= n; i++) lo[i] = 0, hi[i] = q + 1;
	for (int _ = 0; _ < 20; _++) {
		vector<vector<int>> I(q + 1);
		for (int i = 1; i <= n; i++) if (lo[i] + 1 < hi[i]) {
			const int mid = lo[i] + hi[i] >> 1;
			I[mid].push_back(i);
		}
		FT.Init();
		for (int i = 1; i <= q; i++) {
			FT.Update(Q[i].l, Q[i].r, Q[i].x);
			for (int idx : I[i]) {
				ll sum = 0;
				for (int p : pos[idx]) if ((sum += FT.Query(p)) >= v[idx]) break;
				if (sum < v[idx]) lo[idx] = i;
				else hi[idx] = i;
			}
		}
	}
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 1, t; i <= m; i++) cin >> t, pos[t].push_back(i);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cin >> q;
	for (int i = 1; i <= q; i++) cin >> Q[i].l >> Q[i].r >> Q[i].x;
	PBS();
	for (int i = 1; i <= n; i++) {
		if (hi[i] == q + 1) cout << "NIE" << '\n';
		else cout << hi[i] << '\n';
	}
}