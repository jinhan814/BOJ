#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

bool IsValid(const string& s) {
	for (const auto& c : s)
		if (c != 'u' && c != 'm' && isalpha(c))
			return 0;
	return 1;
}

int main() {
	fastio;
	string ans, s, t;
	while (cin >> s) if (IsValid(s)) for (const auto& c: s) {
		if (c == 'u' || c == 'm') {
			t.push_back(c == 'u' ? '1' : '0');
			if (t.size() == 7) ans.push_back((char)(bitset<7>(t).to_ulong())), t.clear();
		}
	}
	cout << ans << '\n';
}