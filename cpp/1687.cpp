#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, mx, pSum[334][334];

bool Check(int l, int r, int i) {
	return pSum[r][i] - pSum[l - 1][i];
}

int Sol(int l, int r) {
	int ret = 0;
	for (int i = 1, j = 1; i <= m; i = j) {
		if (Check(l, r, i)) j++;
		else {
			while (j <= m && !Check(l, r, j)) j++;
			ret = max(ret, j - i);
		}
	}
	return ret * (r - l + 1);
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		for (int j = 0; j < m; j++) pSum[i + 1][j + 1] = pSum[i][j + 1] + (s[j] & 1);
	}
	for (int i = 1; i <= n; i++) for (int j = i; j <= n; j++) mx = max(mx, Sol(i, j));
	cout << mx << '\n';
}