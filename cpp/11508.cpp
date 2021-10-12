#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, ans = 0; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v.rbegin(), v.rend());

	for (int i = 0; i + 2 < n; i += 3) ans += v[i] + v[i + 1];
	for (int i = n - n % 3; i < n; i++) ans += v[i];
	cout << ans << '\n';
}