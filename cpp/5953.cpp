#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, DP = 0, ans = -1e9; cin >> n;
	for (int i = 0; i < n; i++) {
        int t; cin >> t;
        if (ans < t) ans = t;
		if (DP + t >= 0) DP += t, ans < DP ? ans = DP : 0;
		else DP = 0;
	}
	cout << ans << '\n';
}