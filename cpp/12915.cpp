#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int32_t main() {
	fastio;
	int a, ab, b, bc, c; cin >> a >> ab >> b >> bc >> c;

	auto Check = [&](int mid) -> bool {
		const int t1 = a >= mid ? 0 : mid - a;
		if (t1 > ab) return 0;
		const int t2 = b + ab - t1 >= mid ? 0 : mid - (b + ab - t1);
		if (t2 > bc) return 0;
		if (c + bc - t2 < mid) return 0;
		return 1;
	};

	int lo = 0, hi = 1e9 + 7;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (Check(mid)) lo = mid;
		else hi = mid;
	}
	cout << lo << '\n';
}