#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, v[2000], w[2000], cache[2000][2000];

int Sol(int i, int j) { // v[i:], w[j:]에서 얻을 수 있는 최대 점수
	if (i >= n || j >= n) return 0;
	int& ret = cache[i][j];
	if (ret != -1) return ret; ret = 0;
	if (v[i] > w[j]) ret = max(ret, Sol(i, j + 1) + w[j]);
	return ret = max({ ret, Sol(i + 1, j), Sol(i + 1, j + 1) });
}

int main() {
	fastio;
	cin >> n; memset(cache, -1, sizeof cache);
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 0; i < n; i++) cin >> w[i];
	cout << Sol(0, 0) << '\n';
}