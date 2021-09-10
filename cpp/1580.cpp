#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define OOB(x, y) (x < 0 || x >= n || y < 0 || y >= m)
int n, m, sx, sy, ex, ey, dist[20][20][20][20];
string board[20];

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> board[i];
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 'A') sx = i, sy = j;
			if (board[i][j] == 'B') ex = i, ey = j;
		}
	}

	memset(dist, -1, sizeof dist);
	queue<tuple<int, int, int, int>> Q;
	Q.push({ sx, sy, ex, ey }), dist[sx][sy][ex][ey] = 0;
	while (Q.size()) {
		auto [x1, y1, x2, y2] = Q.front(); Q.pop();
		for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) {
			int nx1 = x1 + "000111222"[i] - '1';
			int ny1 = y1 + "012012012"[i] - '1';
			int nx2 = x2 + "000111222"[j] - '1';
			int ny2 = y2 + "012012012"[j] - '1';
			if (OOB(nx1, ny1) || OOB(nx2, ny2)) continue;
			if (board[nx1][ny1] == 'X' || board[nx2][ny2] == 'X') continue;
			if (nx1 == x2 && ny1 == y2 && nx2 == x1 && ny2 == y1) continue;
			if (nx1 == nx2 && ny1 == ny2 || ~dist[nx1][ny1][nx2][ny2]) continue;
			Q.push({ nx1, ny1, nx2, ny2 }), dist[nx1][ny1][nx2][ny2] = dist[x1][y1][x2][y2] + 1;
		}
	}
	cout << dist[ex][ey][sx][sy] << '\n';
}