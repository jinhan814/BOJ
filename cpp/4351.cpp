#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m; cin >> n >> m;
	map<string, int> M;
	for (int i = 0, t; i < n; i++) {
		string s; cin >> s >> t;
		M[s] = t;
	}
	while (m--) {
		int64_t ans = 0;
		for (string s; cin >> s && s != ".";)
			if (M.count(s)) ans += M[s];
		cout << ans << '\n';
	}
}