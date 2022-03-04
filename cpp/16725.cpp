#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;
constexpr int MOD = 1e9 + 9;

template<size_t sz, int MOD>
class Binomial {
private:
	int Pow(int x, int n) {
		int ret = 1;
		for (; n; n >>= 1) {
			if (n & 1) ret = (i64)ret * x % MOD;
			x = (i64)x * x % MOD;
		}
		return ret;
	}
	int Fac[sz + 1], Inv[sz + 1];
public:
	Binomial() {
		Fac[0] = 1;
		for (int i = 1; i <= sz; i++) Fac[i] = (i64)Fac[i - 1] * i % MOD;
		Inv[sz] = Pow(Fac[sz], MOD - 2);
		for (int i = sz; i >= 1; i--) Inv[i - 1] = (i64)Inv[i] * i % MOD;
	}
	int operator() (int n, int r) {
		return (i64)Fac[n] * Inv[r] % MOD * Inv[n - r] % MOD;
	}
};

Binomial<250500, MOD> B;

int Sol(int n, int m, int k) {
	i64 ret = 0;
	for (int i = 0; i <= k / (n + 1); i++) {
		const int t = k - (n + 1) * i;
		ret = (ret + (i64)(i & 1 ? -1 : 1) * B(m, i) * B(m + t - 1, t)) % MOD;
		if (ret < 0) ret += MOD;
	}
	return ret;
}

int main() {
	fastio;
	int n, m, k; cin >> n >> m >> k;
	cout << Sol(n, m, k) << '\n';
}