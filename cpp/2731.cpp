#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

i64 M[11]{ 1 };

i64 Mul(i64 a, i64 b, const i64 MOD) {
	i64 ret = 0;
	for (; a; a >>= 1) {
		if (a & 1) ret += b;
		b = (b << 1) % MOD;
	}
	return ret % MOD;
}

i64 Pow(i64 x, i64 n, const i64 MOD) {
	i64 ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = Mul(ret, x, MOD);
		x = Mul(x, x, MOD);
	}
	return ret;
}

int main() {
	fastio;
	for (int i = 1; i <= 10; i++) M[i] = 10 * M[i - 1];
	int N; cin >> N;
	while (N--) {
		i64 x; cin >> x;
		i64 MOD = M[to_string(x).size()];
		cout << Pow(x, (MOD * 4 / 5 + 1) / 3, MOD) << '\n';
	}
}