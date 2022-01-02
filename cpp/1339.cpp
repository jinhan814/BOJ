#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, res = 0, v[26]{}; cin >> n;
	while (n--) {
		string s; cin >> s;
		reverse(s.begin(), s.end());
		for (int i = 0, t = 1; i < s.size(); i++) v[s[i] - 'A'] += t, t *= 10;
	}
	sort(v, v + 26);
	for (int i = 0; i < 10; i++) res += v[16 + i] * i;
	cout << res << '\n';
}