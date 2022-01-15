#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

constexpr int INF = int(1e18) + 7;

int32_t main() {
	fastio;
	int n, a, b, c, d, mn = INF; cin >> n >> a >> b >> c >> d;
	if (b * c > d * a) swap(a, c), swap(b, d);
	for (int i = 0; i < a; i++) mn = min(mn, i * d + (n - i * c + a - 1) / a * b);
	cout << mn << '\n';
}