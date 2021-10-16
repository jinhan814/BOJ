#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int F(int a, int b, int c) { // ax + by <= c
	if (a + b > c) return 0;
	if (a < b) swap(a, b);
	const int q = a / b, r = a % b, t = (q * c + r) / a;
	const int t1 = (t - 1) / q * (2 * t - q * (1 + (t - 1) / q)) / 2;
	const int t2 = F(b, r, c - b * t);
	return t1 + t2;
}

int G(int a, int b, int n) { // Sum[floor((a * i) / b), { i, 1, n }]
	int ret = 0;
	ret += (a / b) * n * (n + 1) / 2; a %= b;
	ret += F(a, b, a * (n + 1));
	return ret;
}

int32_t main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int a, b, n; cin >> a >> b >> n;
		cout << a * n * (n + 1) / 2 - b * G(a, b, n) << '\n';
	}
}