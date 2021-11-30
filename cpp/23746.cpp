#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	string s, res, v[26];
	for (int i = 0; i < n; i++) {
		string a, b; cin >> a >> b;
		v[b[0] - 'A'] = a;
	}
	cin >> s;
	for (auto& i : s) res += v[i - 'A'];
	int a, b; cin >> a >> b;
	for (int i = a - 1; i < b; i++) cout << res[i];
}