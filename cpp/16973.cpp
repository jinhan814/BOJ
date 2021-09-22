#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int n, m, pSum[1001][1001], dist[1001][1001];
int h, w, sx, sy, ex, ey;

bool Check(int x, int y) {
	--x, --y;
	return pSum[x + h][y + w] - pSum[x + h][y] - pSum[x][y + w] + pSum[x][y] == 0;
}

int BFS() {
	memset(dist, -1, sizeof dist);
	queue<pii> Q;
	Q.push({ sx, sy }), dist[sx][sy] = 0;
	while (Q.size()) {
		auto [x, y] = Q.front(); Q.pop();
		for (int k = 0; k < 4; k++) {
			int nx = x + "1012"[k] - '1';
			int ny = y + "2101"[k] - '1';
			if (nx < 1 || nx + h - 1 > n || ny < 1 || ny + w - 1 > m) continue;
			if (dist[nx][ny] == -1 && Check(nx, ny)) Q.push({ nx, ny }), dist[nx][ny] = dist[x][y] + 1;
		}
	}
	return dist[ex][ey];
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
		cin >> pSum[i][j]; pSum[i][j] += pSum[i][j - 1];
	}
	for (int j = 1; j <= m; j++) for (int i = 1; i <= n; i++) {
		pSum[i][j] += pSum[i - 1][j];
	}
	cin >> h >> w >> sx >> sy >> ex >> ey;
	cout << BFS() << '\n';
}