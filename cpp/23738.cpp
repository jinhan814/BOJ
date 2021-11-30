#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	string s, res; cin >> s;
	for (auto& c : s) res +=
		c == 'B' ? "v" :
		c == 'E' ? "ye" :
		c == 'H' ? "n" :
		c == 'P' ? "r" :
		c == 'C' ? "s" :
		c == 'Y' ? "u" :
		c == 'X' ? "h" :
		string(1, c ^ 32);
	cout << res << '\n';
}