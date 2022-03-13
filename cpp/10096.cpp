#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

bool Check1(const string& s) {
	const int n = s.size() >> 1;
	for (int i = 0; i < n; i++) if (s[i] != s[s.size() - n + i]) return 0;
	return 1;
}

bool Check2(const string& s) {
	const int n = s.size() >> 1;
	int l = 0, r = n;
	while (l <= n && s[l] == s[l + n + 1]) l++;
	while (r > l && s[r] == s[r + n]) r--;
	return r <= l;
}

bool Check3(const string& s) {
	const int n = s.size() >> 1;
	int l = n, r = 2 * n;
	while (l < s.size() && s[l] == s[l - n]) l++;
	while (r > l && s[r] == s[r - n - 1]) r--;
	return r <= l;
}

int main() {
	fastio;
	string s; cin >> s >> s;
	if (~s.size() & 1) return cout << "NOT POSSIBLE" << '\n', 0;
	auto t1 = Check3(s);
	auto t2 = !Check1(s) && Check2(s);
	if (t1 && t2) cout << "NOT UNIQUE" << '\n';
	else if (t1) cout << s.substr(0, s.size() >> 1) << '\n';
	else if (t2) cout << s.substr((s.size() >> 1) + 1) << '\n';
	else cout << "NOT POSSIBLE" << '\n';
}