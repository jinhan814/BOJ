#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int32_t main() {
	fastio;
	int n, cnt = 0; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i], v[i] *= 10;
	sort(v.begin(), v.end());
	for (int i = 0; i < n; i++) {
		auto lo = lower_bound(v.begin(), v.begin() + i, v[i] / 10 * 9);
		auto hi = upper_bound(v.begin(), v.begin() + i, v[i]);
		cnt += hi - lo;
	}
	cout << cnt << '\n';
}