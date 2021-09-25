#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

string DB[] = { ".,!? ", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		string s, ans; cin >> s;
		string::iterator it;
		for (int i = 0, pos = -1; i < s.size(); i++) {
			const char c = s[i];
			if (c == '0') { if (pos != -1) ans.push_back(*it), pos = -1; }
			else if (c - '1' == pos) { if (++it == DB[pos].end()) it = DB[pos].begin(); }
			else it = DB[pos = c - '1'].begin();
		}
		cout << ans << '\n';
	}
}