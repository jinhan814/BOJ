#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

constexpr int MOD = 1e9 + 7;

template<size_t sz = 200'001>
struct FenwickTree {
    int tree[sz + 1]{};
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
	int n, ans = 1, v[200'000]; FenwickTree FT, x; cin >> n;
	for (int i = 0; i < n; i++) cin >> v[i], v[i]++;
    for (int i = 0, sum = 0; i < n; i++) {
        FT.Update(v[i], v[i]), x.Update(v[i], 1), sum += v[i];
        if (!i) continue;
        const int cnt = x.Query(v[i]), t = FT.Query(v[i]);
        const int dist = sum - 2 * t + (2 * cnt - i - 1) * v[i];
        ans = ans * (dist % MOD) % MOD;
    }
    cout << ans << '\n';
}