#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, sx, sy;
string board[600];
bitset<600> visited[600];

int DFS(int x, int y) {
	int ret = board[x][y] == 'P'; visited[x][y] = 1;
	for (int k = 0; k < 4; k++) {
		int nx = x + "1012"[k] - '1';
		int ny = y + "2101"[k] - '1';
		if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
		if (board[nx][ny] == 'X' || visited[nx][ny]) continue;
		ret += DFS(nx, ny);
	}
	return ret;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> board[i];
		for (int j = 0; j < m; j++)
			if (board[i][j] == 'I') sx = i, sy = j;
	}
	if (int t = DFS(sx, sy); t) cout << t << '\n';
	else cout << "TT" << '\n';
}