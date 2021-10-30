#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

struct UnionFind { // union-by-rank ver.
	vector<int> par, v;
	UnionFind(int n) : par(n), v(n) {
		iota(par.begin(), par.end(), 0);
	}
	int Find(int x) {
		return x == par[x] ? x : par[x] = Find(par[x]);
	}
	bool Union(int a, int b) {
		a = Find(a), b = Find(b);
		if (a == b) return 0;
		par[b] = a, v[a] += v[b];
		return 1;
	}
};

int32_t main() {
	fastio;
	int n, mx = 0; cin >> n;
	UnionFind UF(n); vector<int> v(n);
	priority_queue<pair<int, int>> PQ;
	for (int i = 0; i < n; i++) {
		cin >> v[i], UF.v[i] = v[i];
		PQ.push({ v[i], i });
	}

	while (PQ.size()) {
		auto [val, idx] = PQ.top(); PQ.pop();
		for (int j = -1; j <= 1; j += 2) {
			if (0 <= idx + j && idx + j < n && v[idx + j] >= v[idx])
				UF.Union(idx, idx + j);
		}
		mx = max(mx, UF.v[UF.Find(idx)] * val);
	}
	cout << mx << '\n';
}