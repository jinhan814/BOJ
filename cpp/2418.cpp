#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int64_t n, m, k, ans, cache[200][200][101];
string s, board[200];

int64_t DFS(int x, int y, int pos) {
	if (pos + 1 == s.size()) return board[x][y] == s[pos];
	int64_t& ret = cache[x][y][pos];
	if (ret != -1) return ret; ret = 0;
	if (board[x][y] == s[pos]) {
		for (int k = 0; k < 8; k++) {
			int nx = x + "10001222"[k] - '1';
			int ny = y + "22100012"[k] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			ret += DFS(nx, ny, pos + 1);
		}
	}
	return ret;
}

int main() {
	fastio;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) cin >> board[i];
	cin >> s;

	memset(cache, -1, sizeof cache);
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
		ans += DFS(i, j, 0);
	cout << ans << '\n';
}