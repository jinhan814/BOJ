#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		// input
		int k, flag = 0, v[9][9]{}, res[9][9]{}; cin >> k;
		string s[15];
		for (int i = 0; i < 15; i++) cin >> s[i];

		// backtracking
		auto Check = [&](int x, int y, int k) -> bool {
			for (int i = 0; i < 9; i++) {
				if (v[x][i] == k || v[i][y] == k ||
					v[x / 3 * 3 + i / 3][y / 3 * 3 + i % 3] == k) return 0;
			}
			for (int d = 0; d < 2; d++) {
				const int nx = x + "10"[d] - '1';
				const int ny = y + "01"[d] - '1';
				if (nx < 0 || nx >= 9 || ny < 0 || ny >= 9) continue;
				if (x / 3 != nx / 3 || y / 3 != ny / 3) continue;
				if (d & 1) {
					const char c = s[(x / 3 * 5) + (x % 3 & 1 ? 1 : 3)][y];
					if (c == '<' && v[nx][ny] + k >= 10 ||
						c == '>' && v[nx][ny] + k <= 10 ||
						c == '=' && v[nx][ny] + k != 10) return 0;
				}
				else {
					const char c = s[(x / 3 * 5) + (x % 3 << 1)][(y / 3 * 2) + (y % 3 & 1 ? 0 : 1)];
					if (c == '<' && v[nx][ny] + k >= 10 ||
						c == '>' && v[nx][ny] + k <= 10 ||
						c == '=' && v[nx][ny] + k != 10) return 0;
				}
			}
			return 1;
		};

		auto DFS = [&](int x, int y, auto&& DFS) -> void {
			if (flag) return;
			if (x == 9) {
				flag = 1; memcpy(res, v, sizeof v);
				return;
			}
			const int nx = y + 1 < 9 ? x : x + 1, ny = y + 1 < 9 ? y + 1 : 0;
			for (int cur = 1; cur <= 9; cur++) {
				if (!Check(x, y, cur)) continue;
				v[x][y] = cur, DFS(nx, ny, DFS);
				if (flag) return;
				v[x][y] = 0;
			}
		};

		DFS(0, 0, DFS);

		// output
		cout << k << '\n';
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) cout << res[i][j] << ' ';
			cout << '\n';
		}
	}
}