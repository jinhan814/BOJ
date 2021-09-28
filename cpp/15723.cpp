#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, DP[26][26]{}; cin >> n;
	for (int i = 0; i < n; i++) {
		char a, b; string _; cin >> a >> _ >> b;
		DP[a - 'a'][b - 'a'] = 1;
	}

	for (int k = 0; k < 26; k++) for (int i = 0; i < 26; i++) for (int j = 0; j < 26; j++)
		DP[i][j] |= DP[i][k] & DP[k][j];

	int q; cin >> q;
	while (q--) {
		char a, b; string _; cin >> a >> _ >> b;
		cout << (DP[a - 'a'][b - 'a'] ? 'T' : 'F') << '\n';
	}
}