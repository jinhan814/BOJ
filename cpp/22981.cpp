#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int32_t main() {
	fastio;
	int n, k; cin >> n >> k;
	vector<int> v(n);
	for (auto& i : v) cin >> i;
	sort(v.begin(), v.end());

	auto Sol = [&](int idx) -> int {
		int t1 = v[0] * idx;
		int t2 = v[idx] * (n - idx);
		return (k + t1 + t2 - 1) / (t1 + t2);
	};

	int ans = int(1e18) + 7;
	for (int i = 1; i < n; i++) ans = min(ans, Sol(i));
	cout << ans << '\n';
}
