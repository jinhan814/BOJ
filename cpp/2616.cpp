#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, k, mx, pSum[50'001];
int DP[3][50'001];

int main() {
	fastio;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> pSum[i], pSum[i] += pSum[i - 1];
	cin >> k;

	for (int i = k; i <= n; i++) {
		DP[0][i] = max(DP[0][i - 1], pSum[i] - pSum[i - k]);
		DP[1][i] = max(DP[1][i - 1], pSum[i] - pSum[i - k] + DP[0][i - k]);
		DP[2][i] = max(DP[2][i - 1], pSum[i] - pSum[i - k] + DP[1][i - k]);
		mx = max(mx, DP[2][i]);
	}
	cout << mx << '\n';
}