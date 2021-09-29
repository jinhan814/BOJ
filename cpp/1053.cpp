#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int cache[50][50];

int Sol(const string& s, int l, int r) {
	if (r <= l) return 0;
	if (l + 1 == r) return s[l] != s[r];
	int& ret = cache[l][r];
	if (ret != -1) return ret; ret = 1e9;
	ret = min(ret, Sol(s, l + 1, r - 1) + (s[l] != s[r]));
	ret = min(ret, Sol(s, l + 1, r) + 1);
	ret = min(ret, Sol(s, l, r - 1) + 1);
	return ret;
}

int main() {
	fastio;
	string s; cin >> s; memset(cache, -1, sizeof cache);
	int n = s.size(), ans = Sol(s, 0, n - 1);
	for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
		swap(s[i], s[j]); memset(cache, -1, sizeof cache);
		ans = min(ans, Sol(s, 0, n - 1) + 1);
		swap(s[i], s[j]);
	}
	cout << ans << '\n';
}