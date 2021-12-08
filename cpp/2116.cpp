#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, mx, v[10'000][6];

int Sol(int cur) {
	int ret = 0;
	for (int i = 0; i < n; i++) {
		int pos = find(v[i], v[i + 1], cur) - v[i], mx = 0;
		for (int j = 0; j < 6; j++) if (j % 3 != pos % 3) mx = max(mx, v[i][j]);
		cur = v[i][pos < 3 ? pos + 3 : pos - 3], ret += mx;
	}
	return ret;
}

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) for (int j = 0; j < 6; j++) cin >> v[i]["012453"[j] - '0'];
	for (int i = 1; i <= 6; i++) mx = max(mx, Sol(i));
	cout << mx << '\n';
}