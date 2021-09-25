#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int32_t main() {
	fastio;
	for (int a, b, c, d; cin >> a >> b >> c >> d && a;) {
		if (b * c <= a) cout << 0 << '\n';
		else cout << (b * c - a + d - 1) / d << '\n';
	}
}