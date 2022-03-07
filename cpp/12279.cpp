#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using u64 = unsigned long long;

u64 Sol(u64 a, u64 b) {
	if (a == 1 && b == 1) return 1;
	if (a < b) return Sol(a, b - a) << 1;
	return Sol(a - b, b) << 1 | 1;
}

pair<u64, u64> Sol(u64 n) {
	if (n == 1) return { 1, 1 };
	auto [p, q] = Sol(n >> 1);
	if (n & 1) return { p + q, q };
	return { p, p + q };
}

int main() {
	fastio;
	int q; cin >> q;
	for (int i = 1; i <= q; i++) {
		u64 t, a, b; cin >> t >> a;
		if (t & 1) {
			auto res = Sol(a);
			cout << "Case #" << i << ": " << res.first << ' ' << res.second << '\n';
		}
		else {
			cin >> b;
			cout << "Case #" << i << ": " << Sol(a, b) << '\n';
		}
	}
}