#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using tii = tuple<int, int, int>;

int n, a, b, dist[900][900];
string v[30];

int Floyd() {
	memset(dist, 0x3f, sizeof dist);
	for (int x = 0; x < n; x++) for (int y = 0; y < n; y++) {
		for (int k = 0; k < 4; k++) {
			int nx = x + "1012"[k] - '1';
			int ny = y + "2101"[k] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			dist[x * n + y][nx * n + ny] = v[x][y] == v[nx][ny] ? a : b;
		}
		dist[x * n + y][x * n + y] = 0;
	}

	for (int k = 0; k < n * n; k++) {
		for (int i = 0; i < n * n; i++) for (int j = 0; j < n * n; j++)
			dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	}

	int ret = 0;
	for (int i = 0; i < n * n; i++) for (int j = 0; j < n * n; j++) ret = max(ret, dist[i][j]);
	return ret;
}

int main() {
	fastio;
	cin >> n >> a >> b;
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << Floyd() << '\n';
}