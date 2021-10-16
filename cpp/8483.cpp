#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int F(int a, int b, int c) {
	if (a < b) swap(a, b);
	if (c / a <= 100) { // base case
		int ret = 0;
		for (int i = 1; i <= c / a; i++) ret += (c - a * i) / b;
		return ret;
	}
	const int q = a / b, r = a % b, t = (q * c + r) / a;
	const int t1 = (t - 1) / q * (2 * t - q * (1 + (t - 1) / q)) / 2;
	const int t2 = F(b, r, c - b * t);
	return t1 + t2;
}

int32_t main() {
	fastio;
	int a, b, c; cin >> a >> b >> c;
	cout << F(a, b, c) + c / a + c / b + 1 << '\n';
}