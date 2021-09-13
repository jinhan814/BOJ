#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = int64_t;
using i128 = __int128;
using pll = pair<ll, ll>;

struct Random {
	mt19937 rd;
	Random() : rd((unsigned)chrono::steady_clock::now().time_since_epoch().count()) {}
	Random(int seed) : rd(seed) {}
	int GetInt(int l = 0, int r = 32767) {
		return uniform_int_distribution<int>(l, r)(rd);
	}
	double GetDouble(double l = 0, double r = 1) {
		return uniform_real_distribution<double>(l, r)(rd);
	}
} Rand;

struct MillerRabin {
	ll Mul(ll x, ll y, ll MOD) { return (i128)x * y % MOD; }
	ll _pow(ll x, ll n, ll MOD) {
		ll ret = 1; x %= MOD;
		for (; n; n >>= 1) {
			if (n & 1) ret = Mul(ret, x, MOD);
			x = Mul(x, x, MOD);
		}
		return ret;
	}
	bool Check(ll x, ll p) {
		if (x % p == 0) return 0;
		for (ll d = x - 1; ; d >>= 1) {
			ll t = _pow(p, d, x);
			if (d & 1) return t != 1 && t != x - 1;
			if (t == x - 1) return 0;
		}
	}
	bool IsPrime(ll x) {
		for (auto& i : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }) {
			if (x == i) return 1;
			if (x > 40 && Check(x, i)) return 0;
		}
		return x > 40;
	}
};

struct PollardRho : public MillerRabin {
	void Rec(ll n, vector<ll>& v) {
		if (n == 1) return;
		if (~n & 1) { v.push_back(2); Rec(n >> 1, v); return; }
		if (IsPrime(n)) { v.push_back(n); return; }
		ll a, b, c, g = n;
		auto f = [&](ll x) { return (c + Mul(x, x, n)) % n; };
		do {
			if (g == n) {
				a = b = Rand.GetInt() % (n - 2) + 2;
				c = Rand.GetInt() % 20 + 1;
			}
			a = f(a); b = f(f(b)); g = gcd(abs(a - b), n);
		} while (g == 1);
		Rec(g, v); Rec(n / g, v);
	}
	vector<ll> Factorize(ll n) {
        if (n == 1) return { 1 };
		vector<ll> ret; Rec(n, ret);
		sort(ret.begin(), ret.end());
		return ret;
	}
};

int main() {
	fastio;
    ll n; cin >> n; PollardRho P;
    for (auto& i : P.Factorize(n)) cout << i << '\n';
}