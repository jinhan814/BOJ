#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m; cin >> n >> m;
	vector<string> v(n);
	for (int i = 0; i < n; i++) cin >> v[i], m -= v[i].size();

	string ans = v[0];
	for (int i = 1, t = m % (n - 1); i < n; i++) {
		ans += string(m / (n - 1), '_');
		if ('_' < v[i][0] && t || t == n - i) ans.push_back('_'), t--;
		ans += v[i];
	}
	cout << ans << '\n';
}