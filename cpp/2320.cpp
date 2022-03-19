#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, mx, DP[16][1 << 16];
string s[16];

int Sol(int i, int state) {
	int& ret = DP[i][state];
	if (ret) return ret; state |= 1 << i;
	for (int j = 0; j < n; j++) {
		if (state & 1 << j || s[i].back() ^ s[j][0]) continue;
		ret = max(ret, Sol(j, state));
	}
	return ret += s[i].size();
}

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> s[i];
	for (int i = 0; i < n; i++) mx = max(mx, Sol(i, 0));
	cout << mx << '\n';
}