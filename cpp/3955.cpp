#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;
using pii = pair<i64, i64>;

// find x, y s.t. ax + by = 1, 0 <= x < b
pii ExtGCD(i64 a, i64 b) {
	if (b == 0) return { 1, 0 };
	auto res = ExtGCD(b, a % b);
	i64 x = (res.second % b + b) % b;
	return { x, (1 - a * x) / b };
}

i64 Sol(i64 a, i64 b) {
	if (gcd(a, b) != 1) return -1;
	auto res = ExtGCD(b, a).first;
	while (b * res <= 1) res += a;
	if (res > i64(1e9)) return -1;
	return res;
}

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int a, b; cin >> a >> b;
		auto res = Sol(a, b);
		if (res != -1) cout << res << '\n';
		else cout << "IMPOSSIBLE" << '\n';
	}
}