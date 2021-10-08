#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, v[25][25];

int Sol(int x, int y) {
	if (x == n) return 1;
	int ret = 0, cnt = 0;
	int nx = x, ny = y + 1;
	if (ny >= m) nx++, ny = 0;
	for (int k = 0; k < 3; k++) {
		int px = x + "001"[k] - '1';
		int py = y + "010"[k] - '1';
		if (px < 0 || py < 0) continue;
		if (v[px][py]) cnt++;
	}
	if (cnt != 3) {
		v[x][y] = 1;
		ret += Sol(nx, ny);
		v[x][y] = 0;
	}
	return ret += Sol(nx, ny);
}

int main() {
	fastio;
	cin >> n >> m;
	cout << Sol(0, 0) << '\n';
}