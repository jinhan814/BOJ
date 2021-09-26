#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, conv[128], v[7][7], cache[7][7];

int DFS(int x, int y) {
	int& ret = cache[x][y];
	if (ret != -1) return ret; ret = 0;
	if (x + 1 < n) ret = max(ret, DFS(x + 1, y));
	if (y + 1 < n) ret = max(ret, DFS(x, y + 1));
	return ret += v[x][y];
}

int main() {
	fastio;
	cin >> n; memset(cache, -1, sizeof cache);
	for (int i = 0; i < 13; i++) conv["A23456789TJQK"[i]] = i + 1;
	for (int i = n; i --> 0;) for (int j = 0; j < n; j++) {
		string s; cin >> s;
		v[i][j] = conv[s[0]];
	}
	cout << DFS(0, 0) << '\n';
}