#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 1e9 + 7;
using ll = long long;

int Fac[1'000'001];
int Inv[1'000'001];

int Pow(int x, int n) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = (ll)ret * x % MOD;
		x = (ll)x * x % MOD;
	}
	return ret;
}

int Binomial(int n, int k) {
	return (ll)Fac[n] * Inv[k] % MOD * Inv[n - k] % MOD;
}

void Init() {
	Fac[0] = 1;
	for (int i = 1; i <= 1'000'000; i++) Fac[i] = (ll)Fac[i - 1] * i % MOD;
	Inv[1'000'000] = Pow(Fac[1'000'000], MOD - 2);
	for (int i = 1'000'000; i; i--) Inv[i - 1] = (ll)Inv[i] * i % MOD;
}

int Sol(int S, int a, int b, int c) {
	if (a + b + c < S) return 0;
	int ret = 0;
	for (int i = max(0, a + b - S); i <= min(a, a + b + c - S); i++) {
		int t = a + b + c - S - i;
		int t1 = Binomial(a, i);
		int t2 = Binomial(b + c - t, t);
		int t3 = Binomial(b + c - 2 * t, b - t);
		ret = (ret + (ll)t1 * t2 % MOD * t3) % MOD;
	}
	return (ll)ret * Binomial(S, a) % MOD;
}

int main() {
	fastio;
	Init();
	int S, a, b, c; cin >> S >> a >> b >> c;
	if (a < b) swap(a, b);
	if (a < c) swap(a, c);
	if (b < c) swap(b, c);
	cout << Sol(S, a, b, c) << '\n';
}