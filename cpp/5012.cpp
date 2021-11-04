#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

struct Fenwick {
	vector<int> tree; int sz;
	Fenwick(int sz) : tree(sz + 1), sz(sz) {}
	void Update(int i, int val) {
		for (; i <= sz; i += i & -i) tree[i] += val;
	}
	int Query(int i) {
		int ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
};

int32_t main() {
	fastio;
	int n, k = 3; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];

	vector<Fenwick> FT(k, Fenwick(n));
	for (int i = n; i --> 0;) {
		FT[0].Update(v[i], 1);
		for (int j = 1; j < k; j++) FT[j].Update(v[i], FT[j - 1].Query(v[i] - 1));
	}
	cout << FT[k - 1].Query(n) << '\n';
}