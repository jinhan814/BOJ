#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

int n, m, cache[50][50], visited[50][50];
string board[50];

int DFS(int x, int y) {
	int& ret = cache[x][y];
	if (visited[x][y]) return ret = INF;
	if (ret != -1) return ret; ret = 0; visited[x][y] = 1;
	for (int k = 0; k < 4; k++) {
		int nx = x + ("1012"[k] - '1') * (board[x][y] & 15);
		int ny = y + ("2101"[k] - '1') * (board[x][y] & 15);
		if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
		if (board[nx][ny] != 'H') ret = max(ret, DFS(nx, ny));
	}
	return visited[x][y] = 0, ret != INF ? ++ret : INF;
}

int main() {
	fastio;
	cin >> n >> m; memset(cache, -1, sizeof cache);
	for (int i = 0; i < n; i++) cin >> board[i];
	int res = DFS(0, 0);
	cout << (res == INF ? -1 : res) << '\n';
}