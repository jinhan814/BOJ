#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, cnt = 0; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = n - 2, mn = v.back(); i >= 0; i--) {
		if (v[i] >= mn) cnt += v[i] - mn + 1, v[i] = mn - 1;
		mn = min(mn, v[i]);
	}
	cout << cnt << '\n';
}