#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, pSum[366]{}; cin >> n;
	while (n--) {
		int a, b; cin >> a >> b;
		pSum[a - 1]++; pSum[b]--;
	}
	for (int i = 1; i <= 365; i++) pSum[i] += pSum[i - 1];

	int ans = 0;
	for (int i = 0; i <= 365; i++) {
		if (pSum[i] == 0) continue;
		int j = i, mx = pSum[i];
		while (i + 1 <= 365 && pSum[i + 1]) mx = max(mx, pSum[++i]);
		ans += (i - j + 1) * mx;
	}
	cout << ans << '\n';
}