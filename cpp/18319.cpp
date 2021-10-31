#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, k, mx = 0; cin >> n >> k;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int lim = 1; lim <= 1000; lim++) {
		int cnt = 0;
		for (const auto& val : v) cnt += val / lim;
		if (cnt < k / 2) break;
		if (cnt >= k) mx = max(mx, lim * k / 2);
		else {
			const int t1 = cnt - k / 2, t2 = k / 2 - t1;
			sort(v.rbegin(), v.rend(), [lim](int a, int b) { return a % lim < b % lim; });
			int t = 0;
			for (int i = 0; i < min(t2, n); i++) t += v[i] % lim;
			mx = max(mx, t1 * lim + t);
		}
	}
	cout << mx << '\n';
}