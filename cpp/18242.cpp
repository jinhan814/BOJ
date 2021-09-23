#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;
using board = vector<string>;

pii GetUpperLeft(const board& v) {
	const int n = v.size(), m = v[0].size();
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
		if (v[i][j] == '#') return { i, j };
}

pii GetExit(const board& v) {
	const int n = v.size(), m = v[0].size();
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		if (v[i][j] == '#') continue;
		int flag = 0;
		for (int k = 0; k < 4; k++) {
			int nx = i + "1012"[k] - '1';
			int ny = j + "2101"[k] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (v[nx][ny] == '#') flag |= 1 << k;
		}
		if (flag == 0b1010 || flag == 0b0101) return { i, j };
	}
}

string Sol(const board& v) {
	auto [x1, y1] = GetUpperLeft(v);
	auto [x2, y2] = GetExit(v);
	if (x1 == x2) return "UP";
	if (y1 == y2) return "LEFT";
	return x2 - x1 < y2 - y1 ? "RIGHT" : "DOWN";
}

int main() {
	fastio;
	int n, m; cin >> n >> m;
	board v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << Sol(v) << '\n';
}