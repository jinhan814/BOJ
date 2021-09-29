#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using tii = tuple<int, int, int>;

int n, m, ans = 1e9;
int v[10][10], dist[10][10][2001];

int BFS() {
	memset(dist, -1, sizeof dist);
	queue<tii> Q;
	dist[0][0][0] = 0, Q.push({ 0, 0, 0 });
	while (Q.size()) {
		auto [x, y, t] = Q.front(); Q.pop();
		if (x == n - 1 && y == n - 1) return t;
		if (++t > 2000) break;
		if (dist[x][y][t] == -1) dist[x][y][t] = t, Q.push({ x, y, t });
		for (int k = 0; k < 4; k++) {
			int nx = x + "1012"[k] - '1';
			int ny = y + "2101"[k] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (v[nx][ny] == 0 || v[nx][ny] > 1 && t % v[nx][ny]) continue;
			if (v[x][y] > 1 && v[nx][ny] > 1) continue;
			if (dist[nx][ny][t] == -1)
				dist[nx][ny][t] = t, Q.push({ nx, ny, t });
		}
	}
	return 1e9;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> v[i][j];
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
		if (v[i][j]) continue;
		int cnt = 0;
		for (int k = 0; k < 4; k++) {
			int nx = i + "1012"[k] - '1';
			int ny = j + "2101"[k] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (!v[nx][ny]) cnt++;
		}
		if (cnt >= 2) continue;
		v[i][j] = m; ans = min(ans, BFS());
		v[i][j] = 0;
	}
	cout << ans << '\n';
}