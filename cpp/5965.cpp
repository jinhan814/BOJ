#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t
#define OOB(x, y) (x < 1 || x > n || y < 1 || y > n || y > x)

int n, k, mx = -1e18, pSum[701][701];

int32_t main() {
	fastio;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= i; j++) {
		cin >> pSum[i][j];
		pSum[i][j] += pSum[i][j - 1];
	}

	for (int i = 1; i <= n - k + 1; i++) for (int j = 1; j <= i; j++) {
		int sum = 0;
		for (int sz = 1; sz <= min(n - i + 1, 2 * k); sz++) {
			sum += pSum[i + sz - 1][j + sz - 1] - pSum[i + sz - 1][j - 1];
			if (sz >= k) mx = max(mx, sum / (sz * (sz + 1) / 2));
		}
	}

	for (int i = 2 * k - 1; i <= n; i++) for (int j = k; j <= i - k + 1; j++) {
		int sum = 0;
		for (int sz = 1; sz <= 2 * k; sz++) {
			if (OOB(i - sz + 1, j - sz + 1) || OOB(i - sz + 1, j)) break;
			sum += pSum[i - sz + 1][j] - pSum[i - sz + 1][j - sz];
			if (sz >= k) mx = max(mx, sum / (sz * (sz + 1) / 2));
		}
	}

	cout << mx << '\n';
}