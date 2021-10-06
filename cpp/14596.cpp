#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

pair<int, int> Sol(int n, int k) {
	if (n == 2) return { k - 1 & 2 ? 2 : 1, k & 2 ? 2 : 1 };
	const int t = n * n >> 2, sz = n >> 1;
	if (k <= 1 * t) {
		auto [x, y] = Sol(n >> 1, k - 0 * t);
		return { y, x };
	}
	else if (k <= 2 * t) {
		auto [x, y] = Sol(n >> 1, k - 1 * t);
		return { x, y + sz };
	}
	else if (k <= 3 * t) {
		auto [x, y] = Sol(n >> 1, k - 2 * t);
		return { x + sz, y + sz };
	}
	else {
		auto [x, y] = Sol(n >> 1, k - 3 * t);
		return { sz + sz - y + 1, sz - x + 1 };
	}
}

int main() {
	fastio;
	int n, k; cin >> n >> k;
	auto [x, y] = Sol(n, k);
	cout << x << ' ' << y << '\n';
}