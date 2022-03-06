#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

i64 n, m, k, p;
int Fac[1'000'000];
int Inv[1'000'000];

int Pow(int x, int n) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = (i64)ret * x % p;
		x = (i64)x * x % p;
	}
	return ret;
}

void Init() {
	Fac[0] = 1;
	for (int i = 1; i < p; i++) Fac[i] = (i64)Fac[i - 1] * i % p;
	Inv[p - 1] = Pow(Fac[p - 1], p - 2);
	for (int i = p - 1; i >= 1; i--) Inv[i - 1] = (i64)Inv[i] * i % p;
}

int Binomial(i64 n, i64 r) {
	int ret = 1;
	while (n || r) {
		const int cn = n % p, cr = r % p;
		if (cn < cr) ret = 0;
		else ret = ret * ((i64)Fac[cn] * Inv[cr] % p * Inv[cn - cr] % p) % p;
		n /= p, r /= p;
	}
	return ret;
}

int Sol() {
	int ret = 0;
	for (int i = 0; i <= n; i++) {
		if (k - i < 0 || k - i & 1) continue;
		const i64 t1 = Binomial(n, i);
		const i64 t2 = Binomial(n + m + (k - i) / 2 - 1, (k - i) / 2);
		ret = (ret + t1 * t2) % p;
	}
	return ret;
}

int main() {
	fastio;
	cin >> n >> m >> k >> p;
	Init();
	cout << Sol() << '\n';
}