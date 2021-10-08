#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int a, b, n; cin >> a >> b >> n;
	string s; cin >> s; s += string(b, '0');
	vector<int> v;
	for (int i = 0, t1 = 0, t2 = 0; i < s.size(); i++) {
		if (t1 < a) { s[i] & 1 ? t1++ : t1 = 0; continue; }
		s[i] & 1 ? t2 = 0 : t2++;
		if (t2 == b) v.push_back(i + 1), t1 = t2 = 0;
	}
	if (v.empty()) cout << "NIKAD" << '\n';
	else for (auto& i : v) cout << i << '\n';
}