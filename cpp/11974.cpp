#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, ans, l[7], r[7];

int main() {
	fastio;
	cin >> n;
	memset(l + 1, -1, 24);
	memset(r + 1, -1, 24);

	for (int i = 1, pSum = 0; i <= n; i++) {
		int t; cin >> t; (pSum += t) %= 7;
		if (l[pSum] == -1) l[pSum] = r[pSum] = i;
		else r[pSum] = i;
	}

	for (int i = 0; i < 7; i++)
		if (l[i] != -1) ans = max(ans, r[i] - l[i]);
	cout << ans << '\n';
}