#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

short spf[4'000'001];
int cnt[4'000'001];

void Sieve() {
	for (int i = 2; i <= 2'000; i++) {
		if (spf[i]) continue;
		for (int j = i * i; j <= 4'000'000; j += i) if (!spf[j]) spf[j] = i;
	}
}

void Check(int n, int delta) {
	while (spf[n]) {
		cnt[spf[n]] += delta;
		n /= spf[n];
	}
	if (n > 1) cnt[n] += delta;
}

int Pow(int x, int n, const int MOD) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = 1LL * ret * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return ret;
}

int main() {
	fastio;
	Sieve();
	int n, k, MOD, res = 1; cin >> n >> k >> MOD;
	if (k > n - k) k = n - k;
	for (int i = n - k + 1; i <= n; i++) Check(i, 1);
	for (int i = 1; i <= k; i++) Check(i, -1);
	for (int i = 1; i <= n; i++) res = 1LL * res * Pow(i, cnt[i], MOD) % MOD;
	cout << res << '\n';
}