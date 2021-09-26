#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, k, pSum[101][101];
string board[101];

int main() {
	fastio;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		cin >> board[i];
		for (int j = 1; j <= m; j++) {
			pSum[i][j] = pSum[i - 1][j] + pSum[i][j - 1] - pSum[i - 1][j - 1];
			if (board[i][j - 1] == '*') pSum[i][j]++;
		}
	}

	int x = 1, y = 1, mx = 0;
	for (int i = 1; i <= n - k + 1; i++) for (int j = 1; j <= m - k + 1; j++) {
		int sum = pSum[i + k - 2][j + k - 2] - pSum[i + k - 2][j] - pSum[i][j + k - 2] + pSum[i][j];
		if (mx < sum) x = i, y = j, mx = sum;
	}

	for (int i = 1; i + 1 < k; i++) board[x + i][y - 1] = board[x + i][y + k - 1 - 1] = '|';
	for (int i = 1; i + 1 < k; i++) board[x][y + i - 1] = board[x + k - 1][y + i - 1] = '-';
	board[x][y - 1] = board[x][y + k - 1 - 1] = board[x + k - 1][y - 1] = board[x + k - 1][y + k - 1 - 1] = '+';

	cout << mx << '\n';
	for (int i = 1; i <= n; i++) cout << board[i] << '\n';
}