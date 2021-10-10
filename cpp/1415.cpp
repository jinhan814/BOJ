#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

constexpr int SZ = 5e5;
vector<int> p;
int sieve[SZ + 1]; // sieve[i] : IsPrime(i) ? 0 : smallest prime factor

void LinearSieve(int n = SZ) {
	for (int i = 2; i <= n; i++) {
		if (!sieve[i]) p.push_back(i);
		for (auto j : p) {
			if (i * j > n) break;
			sieve[i * j] = j;
			if (i % j == 0) break;
		}
	}
}

int DP[500'001]{ 1 };
int nxt[500'001]{ 1 };

int32_t main() {
	fastio;
	LinearSieve();
	int n, ans = 0; cin >> n;
	map<int, int> M;
	for (int t; n-- && cin >> t; M[t]++);
	for (const auto& [val, cnt] : M) {
		for (int i = 1; i <= cnt; i++) for (int j = 500'000 - i * val; j >= 0; j--)
			nxt[j + i * val] += DP[j];
		memcpy(DP, nxt, sizeof DP);
		memcpy(nxt, DP, sizeof DP);
	}
	for (const auto& i : p) ans += DP[i];
	cout << ans << '\n';
}