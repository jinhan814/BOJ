#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	for (int n; cin >> n && n;) {
		int ans = 1e9;
		for (int i = 0; i <= 1000; i++) for (int j = 0; j <= 100; j++) {
			if (i * i + j * j * j <= n) ans = min(ans, (n - i * i - j * j * j) + i + j);
			else break;
		}
		cout << ans << '\n';
	}
}