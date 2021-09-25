#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;
using ll = long long;
using pii = pair<int, int>;

struct UnionFind {
	vector<int> par, l, r;
	UnionFind(int n) : par(n), l(n), r(n) {
		iota(par.begin(), par.end(), 0);
		iota(l.begin(), l.end(), 0);
		iota(r.begin(), r.end(), 0);
	}
	int Find(int x) {
		return x == par[x] ? x : par[x] = Find(par[x]);
	}
	void Union(int a, int b) {
		a = Find(a), b = Find(b);
		par[b] = a;
		l[a] = min(l[a], l[b]);
		r[a] = max(r[a], r[b]);
	}
	pii operator() (int i) {
		i = Find(i);
		return { l[i], r[i] };
	}
};

int main() {
	fastio;
	int N; cin >> N;
	for (int c = 1; c <= N; c++) {
		int n; string s; cin >> n >> s;
		UnionFind UF(n);
		for (int i = 1; i < n; i++) if (s[i - 1] == '0' && s[i] == '0') UF.Union(i - 1, i);

		ll ans = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == '1') continue;
			const auto [l, r] = UF(i);
			int dist = INF;
			if (l) dist = min(dist, i - l + 1);
			if (r + 1 < n) dist = min(dist, r - i + 1);
			ans += dist;
		}
		cout << "Case #" << c << ": " << ans << '\n';
	}
}