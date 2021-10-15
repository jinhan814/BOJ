#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

bitset<10001> check;

int main() {
	fastio;
	int n, k, ans = 1; cin >> n >> k;
	for (int i = 0, cnt = 0; i < n; i++) {
		int t; cin >> t;
		if (!check[t]) cnt += check[t] = 1;
		if (cnt == k) ans++, check.reset(), cnt = 0;
	}
	cout << ans << '\n';
}