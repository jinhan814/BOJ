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

// v[i] ^ v[i + 1] ^ ... >= m
bool Check(const vector<int>& v, const int i, const int m) {
	if (v.size() - i > 4) return 1;
	int res = 1;
	for (int j = v.size() - 1; j >= i; j--) {
		if (res > 20) return 1;
		int t = 1;
		while (res--) { if ((i64)t * v[j] >= m) return 1; t *= v[j]; }
		res = t;
	}
	return 0;
}

// v[i] ^ v[i + 1] ^ ... % m
int Sol(const vector<int>& v, const int i, const int m) {
	if (m == 1) return 0;
	if (v[i] == 1) return 1;
	if (i == v.size() - 1) return v.back() % m;
	if (gcd(v[i], m) == 1) return Pow(v[i], Sol(v, i + 1, Phi(m)), m);
	const int phi = Phi(m);
	const int res = Sol(v, i + 1, phi);
	if (Check(v, i + 1, phi)) return Pow(v[i], res + phi, m);
	else return Pow(v[i], res, m);
}

int main() {
	fastio;
	int N, m; cin >> N >> m;
	while (N--) {
		int n, pos = -1; cin >> n;
		vector<int> v(n);
		for (int i = 0; i < n; i++) cin >> v[i];
		for (int i = n; i--;) if (v[i] == 1) pos = i;
		if (pos != -1) v.resize(pos + 1);
		cout << Sol(v, 0, m) << '\n';
	}
}