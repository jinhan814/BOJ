#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

vvi Sol_odd(int n) {
	vvi ret(n, vi(n));
	for (int i = 1, x = 0, y = n >> 1; i <= n * n; i++) {
		ret[x][y] = i;
		int nx = (x + n - 1) % n, ny = (y + 1) % n;
		if (ret[nx][ny]) nx = (x + 1) % n, ny = y;
		x = nx, y = ny;
	}
	return ret;
}

vvi Sol_even(int n) {
	vvi ret(n, vi(n));
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
		if ((i % 4 == 0 || i % 4 == 3) ^
			(j % 4 == 1 || j % 4 == 2)) ret[i][j] = i * n + j + 1;
		else ret[n - 1 - i][n - 1 - j] = i * n + j + 1;
	}
	return ret;
}

vvi Sol(int n) {
	if (n & 1) return Sol_odd(n);
	if (n % 4 == 0) return Sol_even(n);
	vvi ret(n, vi(n)), v = Sol_odd(n >> 1);
	for (int d = 0, t = n * n >> 2; d < 4; d++) {
		for (int i = 0; i < n >> 1; i++) for (int j = 0; j < n >> 1; j++) {
			const int x = i + (d == 1 || d == 3) * (n >> 1);
			const int y = j + (d == 1 || d == 2) * (n >> 1);
			ret[x][y] = v[i][j] + d * t;
		}
	}
	for (int i = 0; i < n >> 1; i++) {
		for (int j = 0; j < n - 2 >> 2; j++) swap(ret[i][j], ret[i + (n >> 1)][j]);
		for (int j = 1; j < n - 2 >> 2; j++) swap(ret[i][n - j], ret[i + (n >> 1)][n - j]);
	}
	swap(ret[n >> 2][0], ret[(n >> 1) + (n >> 2)][0]);
	swap(ret[n >> 2][n >> 2], ret[(n >> 1) + (n >> 2)][n >> 2]);
	return ret;
}

int main() {
	fastio;
	int n; cin >> n;
	for (auto& i : Sol(n)) {
		for (auto& j : i) cout << j << ' ';
		cout << '\n';
	}
}