#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

int Pow(int x, int n, const int m) {
	int ret = 1; x %= m;
	for (; n; n >>= 1) {
		if (n & 1) ret = (i64)ret * x % m;
		x = (i64)x * x % m;
	}
	return ret;
}

int Phi(int n) {
	int ret = n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i) continue;
		ret = ret / i * (i - 1);
		while (n % i == 0) n /= i;
	}
	if (n > 1) ret = ret / n * (n - 1);
	return ret;
}

bool Check(int x, int n, const int m) {
	if (x == 1 || n == 0) return 1 >= m;
	int t = x;
	while (--n) { if (t >= 10) return 1; t = Pow(t, t, 1e9); }
	return t >= m;
}

int F(const int x, const int n, const int m) {
	if (m == 1) return 0;
	if (n == 1) return x % m;
	const int phi = Phi(m);
	if (gcd(x, m) == 1) return Pow(x, F(x, n - 1, phi), m);
	return Pow(x, F(x, n - 1, phi) + Check(x, n - 1, phi) * phi, m);
}

int main() {
	fastio;
	int a, b; cin >> a >> b;
	if (Check(a, b, 1e8)) cout << setw(8) << setfill('0');
	cout << F(a, b, 1e8) << '\n';
}