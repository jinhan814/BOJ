#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int conv[128];
constexpr void Init() { for (int i = 0; i < 4; i++) conv["RULD"[i]] = i; }

int main() {
	fastio; Init();
	int n; string s; cin >> n >> s;
	vector<string> board(n, string(n, 0));
	for (int i = 0, x = 0, y = 0; i < s.size(); i++) {
		const int d = conv[s[i]];
		int nx = x + "1012"[d] - '1';
		int ny = y + "2101"[d] - '1';
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
		board[x][y] |= d & 1 ? 1 : 2;
		board[nx][ny] |= d & 1 ? 1 : 2;
		x = nx, y = ny;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cout << ".|-+"[board[i][j]];
		cout << '\n';
	}
}