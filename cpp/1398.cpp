#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N, DP[100]; cin >> N;
	memset(DP, 0x3f, sizeof DP);
	for (int i = 0; i < 100; i++) for (int j = 0; i + 10 * j < 100; j++) for (int k = 0; i + 10 * j + 25 * k < 100; k++) {
		const int val = i + 10 * j + 25 * k;
		DP[val] = min(DP[val], i + j + k);
	}
	while (N--) {
		int64_t n, ans = 0; cin >> n;
		for (; n; n /= 100) ans += DP[n % 100];
		cout << ans << '\n';
	}
}