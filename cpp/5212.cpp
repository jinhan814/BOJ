#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m; cin >> n >> m;
	int xm = 1e9, xM = 0, ym = 1e9, yM = 0;
	vector<string> v(n), w(n, string(m, '.'));
	for (int i = 0; i < n; i++) cin >> v[i];

	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		if (v[i][j] == '.') continue;
		int cnt = 0;
		for (int k = 0; k < 4; k++) {
			int nx = i + "1012"[k] - '1';
			int ny = j + "2101"[k] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (v[nx][ny] == 'X') cnt++;
		}
		if (cnt >= 2) {
			w[i][j] = 'X';
			xm = min(xm, i); xM = max(xm, i);
			ym = min(ym, j); yM = max(yM, j);
		}
	}

	for (int i = xm; i <= xM; i++) {
		for (int j = ym; j <= yM; j++) cout << w[i][j];
		cout << '\n';
	}
}