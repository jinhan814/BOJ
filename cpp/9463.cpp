#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Fenwick {
	int n; vector<int> tree;
	Fenwick(int n) : n(n), tree(n + 1) {}
	void Update(int i, int val) {
		for (; i <= n; i += i & -i) tree[i] += val;
	}
	int Query(int i) {
		int ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
};

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int64_t n, ans = 0; cin >> n;
		vector<int> rev(n + 1); Fenwick FT(n);
		for (int i = 1, t; i <= n; i++) cin >> t, rev[t] = i;
		for (int i = 1, t; i <= n; i++) {
			cin >> t, FT.Update(rev[t], 1);
			ans += i - FT.Query(rev[t]);
		}
		cout << ans << '\n';
	}
}