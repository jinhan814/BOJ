#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 1e9 + 7;
int n, m, DP[1 << 20];

inline int Add(int a, int b) { return (a += b) >= MOD ? a - MOD : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + MOD : a; }
inline int Pow(int x, int n) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = (1LL * ret * x) % MOD;
		x = (1LL * x * x) % MOD;
	}
	return ret;
}

int main() {
	fastio;
	// input
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int state = 0, t; cin >> t;
		for (int j = t; j --> 0 && cin >> t; state |= 1 << t - 1);
		DP[state]++;
	}

	// SOS DP
	for (int i = 0; i < m; i++) for (int mask = 0; mask < 1 << m; mask++)
		if (mask & 1 << i) DP[mask] = Add(DP[mask], DP[mask ^ 1 << i]);

	// get DP
	for (int i = 0; i < 1 << m - 1; i++) swap(DP[i], DP[i ^ (1 << m) - 1]);
	for (int i = 0; i < 1 << m; i++) DP[i] = Pow(2, DP[i]);

	// inclusion-exclusion principle
	int ans = 0;
	for (int i = 0; i < 1 << m; i++) {
		if (__builtin_popcount(i) & 1) ans = Sub(ans, DP[i]);
		else ans = Add(ans, DP[i]);
	}
	cout << ans << '\n';
}