#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;

int f(ll n) {
	int ret = 0;
	for (int i = 0; n; n >>= 1, i++) if (n & 1) ret = i;
	return ret;
}

int main() {
	fastio;
	ll n, k, ans = 0; cin >> n >> k;
	for (int i = 0, j = 0, t = f(k); j <= t; i++) {
		if (n & 1LL << i) continue;
		if (k & 1LL << j++) ans |= 1LL << i;
	}
	cout << ans << '\n';
}