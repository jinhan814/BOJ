#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int DP[30][30];
	for (int c = 1, n, m; cin >> n >> m && n; c++) {
		memset(DP, 0, sizeof DP); DP[0][0] = 1;
		for (int x, y; cin >> x >> y && (x || y); DP[x][y] = -1);
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
			if (DP[i][j] == -1) continue;
			if (i && ~DP[i - 1][j]) DP[i][j] += DP[i - 1][j];
			if (j && ~DP[i][j - 1]) DP[i][j] += DP[i][j - 1];
		}
		cout << "Map " << c << ": ";
		cout << DP[n - 1][m - 1] << '\n';
	}
}