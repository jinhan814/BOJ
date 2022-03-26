#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m;
int P0[1502][1502]; // every #
int P1[1502][1502]; // left lower #
int P2[1502][1502]; // right upper #
string board[1500];

void DFS(int x, int y, int P[][1502]) {
	P[x][y] = 1;
	for (int d = 0; d < 8; d++) {
		const int nx = x + "10001222"[d] - '1';
		const int ny = y + "22100012"[d] - '1';
		if (nx < 0 || nx > n + 1 || ny < 0 || ny > m + 1) continue;
		if (nx && nx <= n && ny && ny <= m && board[nx - 1][ny - 1] != '#') continue;
		if (nx == 0 && ny == 1 || nx == n + 1 && ny == m) continue;
		if (P[nx][ny]) continue;
		DFS(nx, ny, P);
	}
}

int F(int x, int y) {
	int lo = 1, hi = min(n + 1 - x, m + 1 - y) + 1;
	while (lo + 1 < hi) { // [x, x + mid) * [y, y + mid)
		const int mid = lo + hi >> 1;
		if (P0[x + mid - 1][y + mid - 1] -
			P0[x + mid - 1][y - 1] -
			P0[x - 1][y + mid - 1] +
			P0[x - 1][y - 1] == 0) lo = mid;
		else hi = mid;
	}
	return lo;
}

int G(int x, int y, int sz) {
	int lo = 0, hi = sz + 1;
	while (lo + 1 < hi) { // [x, x + mid) * [y, y + mid)
		const int mid = lo + hi >> 1;
		int t1 = P1[x + mid][y + mid], t2 = P2[x + mid][y + mid];
		if (x > 1) t1 -= P1[x - 2][y + mid], t2 -= P2[x - 2][y + mid];
		if (y > 1) t1 -= P1[x + mid][y - 2], t2 -= P2[x + mid][y - 2];
		if (x > 1 && y > 1) t1 += P1[x - 2][y - 2], t2 += P2[x - 2][y - 2];
		if (t1 == 0 || t2 == 0) lo = mid;
		else hi = mid;
	}
	return hi;
}

tuple<int, int, int> Sol() {
	int x = -1, y = -1, sz = 1e9;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
		if (board[i - 1][j - 1] == '#') continue;
		int res1 = F(i, j);
		int res2 = G(i, j, res1);
		if (res2 <= res1 && sz > res2) x = i, y = j, sz = res2;
	}
	return { x, y, sz };
}

int main() {
	fastio;
	// 1. input
	cin >> m >> n;
	for (int i = 0; i < n; i++) cin >> board[i];
	DFS(0, 0, P1), DFS(n + 1, m + 1, P2);
	board[0][0] = board[n - 1][m - 1] = '#';
	for (int i = 0; i <= n + 1; i++) for (int j = 0; j <= m + 1; j++) {
		if (i == 0 || i == n + 1 ||
			j == 0 || j == m + 1 ||
			board[i - 1][j - 1] == '#') P0[i][j] = 1;
	}

	// 2. prefix sum
	for (int i = 1; i <= n + 1; i++) for (int j = 0; j <= m + 1; j++) {
		P0[i][j] += P0[i - 1][j];
		P1[i][j] += P1[i - 1][j];
		P2[i][j] += P2[i - 1][j];
	}
	for (int j = 1; j <= m + 1; j++) for (int i = 0; i <= n + 1; i++) {
		P0[i][j] += P0[i][j - 1];
		P1[i][j] += P1[i][j - 1];
		P2[i][j] += P2[i][j - 1];
	}

	// 3. sol
	auto [x, y, sz] = Sol();
	if (x == -1) cout << "Impossible" << '\n';
	else cout << sz << ' ' << y << ' ' << x << '\n';
}