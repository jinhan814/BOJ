#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int bias = 2000;
int n, conv[128]; string s;
bitset<4001> check[4001];

void Init() {
	for (int i = 0; i < 4; i++) conv["ENWS"[i]] = i;
	for (int i = 0; i <= 4000; i += 2) check[0][i] = 1;
	for (int i = 2; i <= 4000; i += 2) check[i] |= check[0];
}

void DFS(int x, int y) {
	check[x][y] = 1;
	for (int k = 0; k < 4; k++) {
		int nx = x + "1012"[k] - '1';
		int ny = y + "2101"[k] - '1';
		if (nx < 0 || nx > 4000 || ny < 0 || ny > 4000) continue;
		if (!check[nx][ny]) DFS(nx, ny);
	}
}

int main() {
	fastio; Init();
	int n; string s; cin >> n >> s;
	for (int i = 0, x = 0, y = 0; i < n; i++) {
		const int d = conv[s[i]];
		const int dx = "1012"[d] - '1';
		const int dy = "2101"[d] - '1';
		check[2 * x + dx + bias][2 * y + dy + bias] = 1;
		x += dx; y += dy;
	}

	int cnt = 0;
	for (int i = 0; i <= 4000; i++) for (int j = 0; j <= 4000; j++) {
		if (check[i][j]) continue;
		cnt++; DFS(i, j);
	}
	cout << cnt - 1 << '\n';
}