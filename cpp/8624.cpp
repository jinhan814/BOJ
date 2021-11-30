#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int32_t main() {
	fastio;
	int n, k, a, b; cin >> n >> k >> a >> b;

	auto Sol = [n, k](int a, int b, auto&& Sol) -> int {
		if (a > k) return (b - a + 1) * (a + b - 2 * k) / 2;
		if (b <= k) return (b - a + 1) * ((n - k << 1) + a + b) / 2;
		return Sol(a, k, Sol) + Sol(k + 1, b, Sol);
	};

	cout << Sol(a, b, Sol) << '\n';
}