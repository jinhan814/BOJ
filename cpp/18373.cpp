#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

int Pow(int x, int n, const int MOD) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = (i64)ret * x % MOD;
		x = (i64)x * x % MOD;
	}
	return ret;
}

int Fac(int n, const int MOD) {
	int ret = 1;
	for (int i = 2; i <= n; i++) ret = (i64)ret * i % MOD;
	return ret;
}

int Sol(int N, int K, int P) {
	if (N == 2) return N % P;
	if (K >= 4) return 0;
	if (K == 3) return N == 3 && P > 720 ? Fac(720, P) : 0;
	if (N >= 13 || P <= Fac(N, 1e9)) return 0;
	if (N <= 11) return Fac(Fac(N, 1e9), P);
	int t = 1;
	for (int i = 479001601; i < P; i++) t = (i64)t * i % P;
	return (i64)(P - 1) * Pow(t, P - 2, P) % P;
}

int main() {
	fastio;
	int N, K, P; cin >> N >> K >> P;
	cout << Sol(N, K, P) << '\n';
}