#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int Sol(const string& s) {
	auto it = s.begin();
	for (int i = 1; ; i++) {
		const string t = to_string(i);
		for (const auto& c : t) if (*it == c)
			if (++it == s.end()) return i;
	}
}

int main() {
	fastio;
	string s; cin >> s;
	cout << Sol(s) << '\n';
}