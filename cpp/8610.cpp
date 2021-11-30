#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, mx = 0, t, cnt[26]{}; char c; string s; cin >> n >> c >> s;
	for (char& i : s) mx = max(mx, ++cnt[i - 'A']);
	for (int i = 0; i < 26; i++) if (cnt[i] == mx) t = i;
	for (char& i : s) i = (i - t + c - 104) % 26 + 'A';
	cout << s << '\n';
}