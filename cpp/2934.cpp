#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

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

int main() {
	fastio;
	int n; cin >> n;
	Fenwick FT(100'001);
	while (n--) {
		int a, b, res = 0; cin >> a >> b;
		if (int t = FT.Query(a); t) FT.Update(a, -t), FT.Update(a + 1, t), res += t;
		if (int t = FT.Query(b); t) FT.Update(b, -t), FT.Update(b + 1, t), res += t;
		cout << res << '\n'; FT.Update(a + 1, 1), FT.Update(b, -1);
	}
}