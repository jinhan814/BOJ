#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define OOB(x, y) (x < 0 || x >= n || y < 0 || y >= m)

constexpr int MOD = 1e9 + 9;
using pii = pair<int, int>;

int n, m, dist[400][400], DP[400][400];

void BFS() {
	memset(dist, -1, sizeof dist);
	queue<pii> Q;
	dist[0][0] = 0, Q.push({ 0, 0 }), DP[0][0] = 1;
	while (Q.size()) {
		auto [x, y] = Q.front(); Q.pop();
		for (int k = 0; k < 8; k++) {
			int nx = x + "10013443"[k] - '2';
			int ny = y + "43100134"[k] - '2';
			if (OOB(nx, ny)) continue;
			if (dist[nx][ny] == -1) dist[nx][ny] = dist[x][y] + 1, Q.push({ nx, ny }), DP[nx][ny] = DP[x][y];
			else if (dist[nx][ny] == dist[x][y] + 1) (DP[nx][ny] += DP[x][y]) %= MOD;
		}
	}
}

int main() {
	fastio;
	cin >> n >> m; BFS();
	if (dist[n - 1][m - 1] == -1) cout << "None" << '\n';
	else cout << dist[n - 1][m - 1] << ' ' << DP[n - 1][m - 1] << '\n';
}