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
    int64_t n, m, ans{}; cin >> n >> m;
    vector<int> v[n + 1]; Fenwick FT(n);
    for (int a, b; m-- && cin >> a >> b; v[a].push_back(b));
    for (int i = 1; i <= n; i++) {
        sort(v[i].begin(), v[i].end());
        for (const auto& j : v[i]) ans += FT.Query(n) - FT.Query(j), FT.Update(j, 1);
    }
    cout << ans << '\n';
}