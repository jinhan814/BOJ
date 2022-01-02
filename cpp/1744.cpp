#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	vector<int> v(n), DP(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v.begin(), v.end()); DP[0] = v[0];
	for (int i = 1; i < n; i++) {
		int t1 = (i > 1 ? DP[i - 2] : 0) + v[i - 1] * v[i];
		int t2 = DP[i - 1] + v[i];
		DP[i] = max(t1, t2);
	}
	cout << DP[n - 1] << '\n';
}