#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, sx, sy, mx, pos, ans[4];
string board[500];
bitset<4> check[500][500];

int Sol(int x, int y, int d) {
	if (x < 0 || x >= n || y < 0 || y >= m || board[x][y] == 'C') return 0;
	if (check[x][y][d]) return -1;
	int ret = check[x][y][d] = 1;
	int nd = board[x][y] == '.' ? d : board[x][y] == '/' ? "1032"[d] - '0' : "3210"[d] - '0';
	int nx = x + "1012"[nd] - '1';
	int ny = y + "2101"[nd] - '1';
	int t = Sol(nx, ny, nd);
	if (t == -1) return -1;
	return ret + t;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> board[i];
	cin >> sx >> sy; --sx, --sy;
	for (int i = 0; i < 4; i++) {
		if ((ans[i] = Sol(sx, sy, i)) == -1) ans[i] = 1e9 + 7;
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) check[i][j].reset();
	}
	for (const auto& i : { 1, 0, 3, 2 }) if (mx < ans[i]) mx = ans[i], pos = i;
	cout << "RULD"[pos] << '\n' << (mx == 1e9 + 7 ? "Voyager" : to_string(mx)) << '\n';
}