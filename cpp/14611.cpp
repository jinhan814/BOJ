#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;
using tii = tuple<i64, int, int>;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

int n, m, v[300][300];
i64 dist[300][300];

i64 Dijkstra() {
	memset(dist, 0x3f, sizeof dist);
	priority_queue<tii, vector<tii>, greater<>> PQ;
	for (int i = 1; i < n; i++) if (~v[i][0]) PQ.push({ dist[i][0] = v[i][0], i, 0 });
	for (int i = 1; i < m; i++) if (~v[n - 1][i]) PQ.push({ dist[n - 1][i] = v[n - 1][i], n - 1, i });
	while (PQ.size()) {
		auto [cdist, x, y] = PQ.top(); PQ.pop();
		if (x == 0 || y == m - 1) return cdist;
		if (dist[x][y] != cdist) continue;
		for (int d = 0; d < 8; d++) {
			const int nx = x + "10001222"[d] - '1';
			const int ny = y + "22100012"[d] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (!~v[nx][ny] || dist[nx][ny] <= cdist + v[nx][ny]) continue;
			PQ.push({ dist[nx][ny] = cdist + v[nx][ny], nx, ny });
		}
	}
	return -1;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		cin >> v[i][j];
		if (v[i][j] == -2) v[i][j] = 0;
	}
	cout << Dijkstra() << '\n';
}