#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int Sol(const string& s) {
	const int n = s.size();
	int ret = 0, cnt = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '(') {
			if (cnt == n - i) cnt--, ret++;
			else cnt++;
		}
		else {
			if (!cnt) cnt++, ret++;
			else cnt--;
		}
	}
	return ret;
}

int main() {
	fastio;
	string s; cin >> s;
	cout << Sol(s) << '\n';
}