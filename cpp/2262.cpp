#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, res = 0; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	while (--n) {
		int mx = 0, t;
		for (int i = 1; i <= n; i++) if (v[mx] < v[i]) mx = i;
		if (mx && mx < n) t = v[mx - 1] > v[mx + 1] ? -1 : 1;
		else t = mx < n ? 1 : -1;
		res += v[mx] - v[mx + t];
		if (t == -1) mx--;
		v[mx] = min(v[mx], v[mx + 1]);
		v.erase(v.begin() + mx + 1);
	}
	cout << res << '\n';
}