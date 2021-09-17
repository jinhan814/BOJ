#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int main() {
	fastio;
	int n, m; cin >> n >> m;
	vector<pii> _v(n);
	for (auto& [a, b] : _v) cin >> a >> b;
	sort(_v.begin(), _v.end());

	vector<int> v(n), w(n), DP(n);
	for (int i = 0; i < n; i++) tie(v[i], w[i]) = _v[i];

	for (int i = 0; i < n; i++) {
		auto it = upper_bound(v.begin(), v.end(), v[i] - m);
		int t = it == v.begin() ? 0 : DP[it - v.begin() - 1];
		DP[i] = max(i ? DP[i - 1] : 0, w[i] + t);
	}
	cout << DP[n - 1] << '\n';
}