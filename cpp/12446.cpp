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

// F(x, n) >= m, 1 <= n, m <= 1000
bool Check(const int x, const int n, const int m) {
	if (n == 0 || x == 1) return x >= m;
	if (n == 1 && x <= 5) return Pow(x, x, 1e9) >= m;
	return 1;
}

int cache[1 << 20];

// F(x, n) % m
int Sol(const int x, const int n, const int m) {
	if (m == 1) return 0;
	if (n == 0) return x % m;
	int& ret = cache[n | m << 10];
	if (ret != -1) return ret;
	const int phi = Phi(m);
	const int x1 = Sol(x, n - 1, m);
	const int x2 = Sol(x, n - 1, phi);
	return ret = Pow(x1, x2 + Check(x, n - 1, phi) * phi, m);
}

int main() {
	fastio;
	int N; cin >> N;
	for (int i = 1; i <= N; i++) {
		memset(cache, -1, sizeof cache);
		int x, n, m; cin >> x >> n >> m;
		cout << "Case #" << i << ": " << Sol(x, n, m) << '\n';
	}
}