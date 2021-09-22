#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define OOB(x, y) (x < 0 || x >= n || y < 0 || y >= m)
constexpr int dx[] = { 0, -1, 0, 1 };
constexpr int dy[] = { 1, 0, -1, 0 };

constexpr int INF = 0x3f3f3f3f;
using Info = tuple<int, int, int, int>;

int n, m, board[1000][1000];
int dist[1000][1000][2];

enum { RED, PINK, ORANGE, BLUE, PURPLE };

int BFS() {
	memset(dist, 0x3f, sizeof dist);
	priority_queue<Info, vector<Info>, greater<Info>> PQ;
	PQ.push({ dist[0][0][0] = 0, 0, 0, 0 });
	while (PQ.size()) {
		auto [cdist, x, y, state] = PQ.top(); PQ.pop();
		if (dist[x][y][state] != cdist) continue;
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k], ny = y + dy[k], nstate = state, cost = 1;
			if (OOB(nx, ny) || board[nx][ny] == RED || board[nx][ny] == BLUE && !state) continue;
			if (board[nx][ny] == ORANGE) nstate = 1;
			else if (board[nx][ny] == PURPLE) {
				nstate = 0;
				while (board[nx][ny] == PURPLE &&
					!OOB(nx + dx[k], ny + dy[k]) &&
					board[nx + dx[k]][ny + dy[k]] != RED &&
					(state || board[nx + dx[k]][ny + dy[k]] != BLUE))
					nx += dx[k], ny += dy[k], cost++;
			}
			if (dist[nx][ny][nstate] > cdist + cost)
                PQ.push({ dist[nx][ny][nstate] = cdist + cost, nx, ny, nstate });
		}
	}
	int ret = min(dist[n - 1][m - 1][0], dist[n - 1][m - 1][1]);
	return ret == INF ? -1 : ret;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];
	cout << BFS() << '\n';
}