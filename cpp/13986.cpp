#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m; cin >> n >> m;
	vector<string> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = n - 1; i >= 0; i--) for (int j = 0; j < m; j++) {
		if (v[i][j] != 'o') continue;
		for (int t = i + 1; t < n && v[t][j] == '.'; t++) swap(v[t][j], v[t - 1][j]);
	}
	for (int i = 0; i < n; i++) cout << v[i] << '\n';
}