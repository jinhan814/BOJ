#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t
using pii = pair<int, int>;

int32_t main() {
	fastio;
	int n, ans, sum = 0; cin >> n;
	vector<pii> v(n);
	for (auto& [a, b] : v) cin >> a >> b, sum += b;
	sort(v.begin(), v.end());

	for (int i = 0, t = 0; i < n; i++) {
		if (t < sum - t) ans = v[i].first;
		t += v[i].second;
	}
	cout << ans << '\n';
}