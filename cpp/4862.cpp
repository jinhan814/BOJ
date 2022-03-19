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
	while (n--) { if (x >= 10) return 1; x = Pow(x, x, 1e9); }
	return x >= m;
}

int F(const int x, const int n, const int m) {
	if (m == 1) return 0;
	if (n == 1) return x % m;
	const int phi = Phi(m);
	return Pow(x, F(x, n - 1, phi) + Check(x, n - 1, phi) * phi, m);
}

int main() {
	fastio;
	for (int a, b, c; cin >> a && a;) {
		cin >> b >> c;
		cout << setw(c) << setfill('0');
		cout << F(a, b, Pow(10, c, 1e9)) << '\n';
	}
}