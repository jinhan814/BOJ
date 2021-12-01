#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int main() {
	fastio;
	for (int c = 1, n; cin >> n && n; c++) {
		int v[9][9]{}; set<pii> S;
		for (int i = 1; i < 10; i++) for (int j = i + 1; j < 10; j++) S.insert({ i, j });
		while (n--) {
			int a, b; string s1, s2; cin >> a >> s1 >> b >> s2;
			v[s1[0] - 'A'][s1[1] - '1'] = a;
			v[s2[0] - 'A'][s2[1] - '1'] = b;
			S.erase({ min(a, b), max(a, b) });
		}
		for (int i = 1; i < 10; i++) {
			string s; cin >> s;
			v[s[0] - 'A'][s[1] - '1'] = i;
		}

		auto Check = [&](int x, int y, int k) -> bool {
			for (int i = 0; i < 9; i++)
				if (v[x][i] == k || v[i][y] == k) return 0;
			for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)
				if (v[x / 3 * 3 + i][y / 3 * 3 + j] == k) return 0;
			return 1;
		};

		auto DFS = [&](int x, int y, auto&& DFS) -> bool {
			if (x >= 9) return 1;
			int nx = x, ny = y + 1;
			if (ny >= 9) nx++, ny = 0;
			if (v[x][y]) return DFS(nx, ny, DFS);
			for (auto [_x, _y] : vector<pii>{ { x + 1, y }, { x, y + 1 } }) {
				if (_x >= 9 || _y >= 9 || v[_x][_y]) continue;
				auto _S = S;
				for (auto& [t1, t2] : _S) {
					S.erase({ t1, t2 });
					for (auto [t1, t2] : vector<pii>{ { t1, t2 }, { t2, t1 } }) {
						if (Check(x, y, t1)) {
							v[x][y] = t1;
							if (Check(_x, _y, t2)) {
								v[_x][_y] = t2;
								if (DFS(nx, ny, DFS)) return 1;
								v[_x][_y] = 0;
							}
							v[x][y] = 0;
						}
					}
					S.insert({ t1, t2 });
				}
			}
			return 0;
		};
		DFS(0, 0, DFS);

		cout << "Puzzle " << c << '\n';
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) cout << v[i][j];
			cout << '\n';
		}
	}
}