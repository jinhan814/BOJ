#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; bitset<101> DP[101]; cin >> n;
	for (int i = 1; i < n; i++) {
		int t; cin >> t;
		for (int j; t-- && cin >> j; DP[i][j] = 1);
	}

	for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
		if (DP[i][k] && DP[k][j]) DP[i][j] = 1;

	bool flag = 0;
	for (int i = 1; i <= n; i++) if (DP[1][i] && !DP[n][i] && DP[i][i]) flag = 1;
	cout << (flag ? "CYCLE" : "NO CYCLE") << '\n';
}