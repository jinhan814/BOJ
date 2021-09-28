#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, mx, pSum1[752][752], pSum2[752][752];

inline bool IsPossible(int i, int j, int k) {
	const int sz = j - i >> 1;
	if (k - sz < 1 || k + sz > m) return 0;
	if (pSum1[i + sz][k - sz] - pSum1[i - 1][k + 1] != sz + 1) return 0;
	if (pSum2[i + sz][k + sz] - pSum2[i - 1][k - 1] != sz + 1) return 0;
	if (pSum1[j][k] - pSum1[j - sz - 1][k + sz + 1] != sz + 1) return 0;
	if (pSum2[j][k] - pSum2[j - sz - 1][k - sz - 1] != sz + 1) return 0;
	return 1;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		string s; cin >> s;
		for (int j = 1; j <= m; j++) {
			pSum1[i][j] = pSum2[i][j] = s[j - 1] & 1;
			if (j + 1 <= m) pSum1[i][j] += pSum1[i - 1][j + 1];
			if (j - 1 >= 1) pSum2[i][j] += pSum2[i - 1][j - 1];
		}
	}
	for (int i = 1; i <= n; i++) {
		pSum1[i][0] += pSum1[i - 1][1];
		pSum2[i][m + 1] += pSum2[i - 1][m];
	}
	for (int i = 0; i <= m + 1; i++) {
		if (i <= n) pSum1[n + 1][i] += pSum1[n][i + 1];
		if (i >= 1) pSum2[n + 1][i] += pSum2[n][i - 1];
	}
	for (int i = 1; i <= n; i++) for (int j = i; j <= n; j += 2) for (int k = 1; k <= m; k++) {
		if (IsPossible(i, j, k)) mx = max(mx, j - i + 2 >> 1);
	}
	cout << mx << '\n';
}