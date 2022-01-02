#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

constexpr int MOD = 1e5;
int n, cache[200][200];
string s;

bool F(int l, int r) {
	if (s[l] == '?') return string(")]}?").find(s[r]) != -1;
	if (s[r] == '?') return string("([{").find(s[l]) != -1;
	if (s[l] == '(') return s[r] == ')';
	if (s[l] == '[') return s[r] == ']';
	if (s[l] == '{') return s[r] == '}';
	return 0;
}

int Cnt(int l, int r) {
	return s[l] == '?' && s[r] == '?' ? 3 : 1;
}

int Sol(int l, int r) {
	if (r < l) return 1;
	if ((r - l + 1) & 1) return 0;
	int& ret = cache[l][r];
	if (ret != -1) return ret; ret = 0;
	for (int i = 1; i < r - l + 1; i += 2) {
		if (F(l, l + i)) ret += Sol(l + 1, l + i - 1) * Sol(l + i + 1, r) * Cnt(l, l + i);
		if (ret >= MOD) ret = MOD + ret % MOD;
	}
	return ret;
}

int32_t main() {
	fastio;
	memset(cache, -1, sizeof cache);
	cin >> n >> s;
	auto res = Sol(0, n - 1);
	if (res < MOD) cout << res << '\n';
	else cout << setw(5) << setfill('0') << res - MOD << '\n';
}