#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define double long double

int n, x, y, k;
double cache[50][50][50];

double DFS(int x, int y, int cnt) {
	if (cnt == k) return 1.0;
	double& ret = cache[x][y][cnt];
	if (!isnan(ret)) return ret; ret = 0;
	for (int d = 0; d < 8; d++) {
		int nx = x + "10013443"[d] - '2';
		int ny = y + "43100134"[d] - '2';
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
		ret += DFS(nx, ny, cnt + 1) / 8;
	}
	return ret;
}

int main() {
	fastio;
	memset(cache, -1, sizeof cache);
	cin >> n >> x >> y >> k;
	cout << fixed << setprecision(20) << DFS(x - 1, y - 1, 0) << '\n';
}