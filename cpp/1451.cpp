#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int n, m, pSum[51][51];

int F(int x1, int y1, int x2, int y2) { // [x1, x2] * [y1, y2]
	return pSum[x2][y2] - pSum[x1 - 1][y2] - pSum[x2][y1 - 1] + pSum[x1 - 1][y1 - 1];
}

int Sol_2_box(int x1, int y1, int x2, int y2) {
	int ret = 0;
	for (int i = x1; i < x2; i++) ret = max(ret, F(x1, y1, i, y2) * F(i + 1, y1, x2, y2));
	for (int j = y1; j < y2; j++) ret = max(ret, F(x1, y1, x2, j) * F(x1, j + 1, x2, y2));
	return ret;
}

int Sol_3_box() {
	int ret = 0;
	for (int i = 1; i < n; i++) {
		ret = max(ret, F(1, 1, i, m) * Sol_2_box(i + 1, 1, n, m));
		ret = max(ret, Sol_2_box(1, 1, i, m) * F(i + 1, 1, n, m));
	}
	for (int j = 1; j < m; j++) {
		ret = max(ret, F(1, 1, n, j) * Sol_2_box(1, j + 1, n, m));
		ret = max(ret, Sol_2_box(1, 1, n, j) * F(1, j + 1, n, m));
	}
	return ret;
}

int32_t main() {
	fastio;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		string s; cin >> s;
		for (int j = 1; j <= m; j++) pSum[i][j] += pSum[i][j - 1] + (s[j - 1] & 15);
		for (int j = 1; j <= m; j++) pSum[i][j] += pSum[i - 1][j];
	}
	cout << Sol_3_box() << '\n';
}