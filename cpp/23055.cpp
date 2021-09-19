#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	vector<string> s(n, string(n, ' '));
	for (int i = 0; i < n; i++) {
		s[i][0] = s[i][n - 1] = '*';
		s[0][i] = s[n - 1][i] = '*';
		s[i][i] = s[n - 1 - i][i] = '*';
	}
	for (const auto& i : s) cout << i << '\n';
}