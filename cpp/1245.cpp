#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define OOB(x, y) (x < 0 || x >= n || y < 0 || y >= m)
using pii = pair<int, int>;

int n, m, cnt, board[100][100];
bitset<100> visited[100];

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		if (visited[i][j]) continue;
		queue<pii> Q; int mx = -1e9;
		visited[i][j] = 1, Q.push({ i, j });
		while (Q.size()) {
			auto [x, y] = Q.front(); Q.pop();
			for (int k = 0; k < 8; k++) {
				int nx = x + "10001222"[k] - '1';
				int ny = y + "22100012"[k] - '1';
				if (OOB(nx, ny)) continue;
				if (board[nx][ny] == board[x][y] && !visited[nx][ny]) visited[nx][ny] = 1, Q.push({ nx, ny });
				else if (board[nx][ny] != board[x][y]) mx = max(mx, board[nx][ny]);
			}
		}
		if (mx < board[i][j]) cnt++;
	}
	cout << cnt << '\n';
}