#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

int main() {
	fastio;
	int n, m; cin >> n >> m;
	vector<string> board(n);
	for (int i = 0; i < n; i++) cin >> board[i];
	int sx, sy, ex, ey; cin >> sx >> sy >> ex >> ey; --sx, --sy, --ex, --ey;

	auto BFS = [&]() -> bool {
		vvi visited(n, vi(m)); queue<pii> Q;
		Q.push({ sx, sy }), visited[sx][sy] = 1;
		while (Q.size()) {
			auto [x, y] = Q.front(); Q.pop();
			for (int k = 0; k < 4; k++) {
				int nx = x + "1012"[k] - '1';
				int ny = y + "2101"[k] - '1';
				if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				if (board[nx][ny] == 'X' || visited[nx][ny]) continue;
				Q.push({ nx, ny }), visited[nx][ny] = 1;
			}
		}
		return visited[ex][ey];
	};

	if (sx == ex && sy == ey) {
		bool flag = 0;
		for (int k = 0; k < 4; k++) {
			int nx = sx + "1012"[k] - '1';
			int ny = sy + "2101"[k] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (board[nx][ny] == '.') flag = 1;
		}
		cout << (flag ? "YES" : "NO") << '\n';
	}
	else if (board[ex][ey] == 'X') {
		board[ex][ey] = '.';
		cout << (BFS() ? "YES" : "NO") << '\n';
	}
	else {
		bool flag = 0;
		for (int k = 0; k < 4; k++) {
			int nx = ex + "1012"[k] - '1';
			int ny = ey + "2101"[k] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (board[nx][ny] == '.') {
				board[nx][ny] = 'X';
				flag |= BFS();
				board[nx][ny] = '.';
			}
		}
		cout << (flag ? "YES" : "NO") << '\n';
	}
}