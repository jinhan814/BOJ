#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;

ll Mul(ll a, ll b, const ll MOD) { // a*b % MOD
    return __int128(a) * b % MOD;
}

ll Pow(ll x, ll n, const ll MOD) { // x^n % MOD
	ll ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = Mul(ret, x, MOD);
		x = Mul(x, x, MOD);
	}
	return ret;
}

ll F(ll x, ll n, const ll MOD) { // (x^0 + ... + x^n-1) % MOD
	if (n == 1) return 1;
	ll res = Mul(F(x, n >> 1, MOD), 1 + Pow(x, n >> 1, MOD), MOD);
	if (n & 1) res += Pow(x, n - 1, MOD);
	if (res >= MOD) res -= MOD;
	return res;
}

int main() {
	fastio;
	ll m, a, c, x, n, g; cin >> m >> a >> c >> x >> n >> g;
	cout << (Mul(x, Pow(a, n, m), m) + Mul(F(a, n, m), c, m)) % m % g << '\n';
}