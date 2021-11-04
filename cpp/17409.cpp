#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 1e9 + 7;

struct Fenwick {
	vector<int> tree; int sz;
	Fenwick(int sz) : tree(sz + 1), sz(sz) {}
	void Update(int i, int val) {
		for (; i <= sz; i += i & -i) if ((tree[i] += val) >= MOD) tree[i] -= MOD;
	}
	int Query(int i) {
		int ret = 0;
		for (; i; i -= i & -i) if ((ret += tree[i]) >= MOD) ret -= MOD;
		return ret;
	}
};

int main() {
	fastio;
	int n, k; cin >> n >> k;
	vector<Fenwick> FT(k, Fenwick(n));
	for (int i = 0; i < n; i++) {
		int t; cin >> t; FT[0].Update(t, 1);
		for (int j = 1; j < k; j++) FT[j].Update(t, FT[j - 1].Query(t - 1));
	}
	cout << FT[k - 1].Query(n) << '\n';
}