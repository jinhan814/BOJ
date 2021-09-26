#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, v[100'001], cache[100'001][3];

int DFS(int cur, int cnt) {
	int& ret = cache[cur][cnt];
	if (ret != -1) return ret;
	if (cnt == 1) return ret = DFS(cur - 1, 0) + v[cur];
	if (cnt == 2) return ret = DFS(cur - 1, 1) + v[cur] / 2;
	return ret = max({ DFS(cur - 1, 0), DFS(cur - 1, 1), DFS(cur - 1, 2) });
}

int main() {
	fastio;
	cin >> n; memset(cache, -1, sizeof cache);
	for (int i = 0; i < n; i++) cin >> v[i];
	cache[0][0] = 0, cache[0][1] = v[0], cache[0][2] = -1e9;
	cout << DFS(n, 0) << '\n';
}