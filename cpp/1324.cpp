#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, v[2][1001], cache[1001][1001];

int DFS(int i, int j) {
	int& ret = cache[i][j];
	if (ret != -1) return ret; ret = 1;
	for (int ni = i + 1; ni <= n; ni++) for (int nj = j + 1; nj <= n; nj++) {
		if (v[0][i] >= v[0][ni] || v[0][ni] != v[1][nj]) continue;
		ret = max(ret, DFS(ni, nj) + 1);
	}
	return ret;
}

int main() {
	fastio;
	cin >> n; memset(cache, -1, sizeof cache);
	for (int i = 1; i <= n; i++) cin >> v[0][i];
	for (int i = 1; i <= n; i++) cin >> v[1][i];
	cout << DFS(0, 0) - 1 << '\n';
}