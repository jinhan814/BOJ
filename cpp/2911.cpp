#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t
using pii = pair<int, int>;

struct UnionFind {
	vector<int> par;
	UnionFind(int n) : par(n) {
		iota(par.begin(), par.end(), 0);
	}
	int Find(int x) {
		return x == par[x] ? x : par[x] = Find(par[x]);
	}
	bool Union(int a, int b) {
		a = Find(a), b = Find(b);
		if (a == b) return 0;
		par[b] = a; return 1;
	}
};

int32_t main() {
	fastio;
	int n, m, ans = 0; cin >> n >> m;
	vector<pii> _v(n);
	for (auto& [a, b] : _v) cin >> a >> b;
	sort(_v.begin(), _v.end());

	vector<int> v(n); vector<pii> w(n);
	for (int i = 0; i < n; i++) {
		v[i] = _v[i].second;
		w[i] = { v[i], i };
	}
	sort(w.begin(), w.end());

	UnionFind UF(n);
	for (int i = 0, cnt = 1; i < n; i++, cnt++) {
		int pos = w[i].second, diff = w[i].first - (i + 1 < n ? w[i + 1].first : 0);
		if (pos - 1 >= 0 && v[pos] <= v[pos - 1]) cnt -= UF.Union(pos, pos - 1);
		if (pos + 1 <  n && v[pos] <= v[pos + 1]) cnt -= UF.Union(pos, pos + 1);
		ans += diff * cnt;
	}
	cout << ans << '\n';
}