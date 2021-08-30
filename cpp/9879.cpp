#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, k, x, y, v[500][500];
bitset<500> check[500];

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> v[i][j];
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		int t; cin >> t;
		if (t) check[i][j] = t, k++, x = i, y = j;
	}

	auto Check = [&](int mid) -> bool {
		int cnt = 0;
		bitset<500> visited[500];

		auto DFS = [&](int x, int y, auto&& DFS) -> void {
			visited[x][y] = 1; cnt += check[x][y];
			for (int k = 0; k < 4; k++) {
				int nx = x + "1012"[k] - '1';
				int ny = y + "2101"[k] - '1';
				if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				if (visited[nx][ny] || abs(v[x][y] - v[nx][ny]) > mid) continue;
				DFS(nx, ny, DFS);
			}
		};
		DFS(x, y, DFS);

		return cnt == k;
	};

	int lo = -1, hi = 1e9;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (!Check(mid)) lo = mid;
		else hi = mid;
	}
	cout << hi << '\n';
}