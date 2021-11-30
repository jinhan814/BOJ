#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m, k, mx = 0, cnt[1001]{}; cin >> n >> m >> k;
	for (int t; k-- && cin >> t; mx = max(mx, ++cnt[(t - 1) / m]));
	for (int i = mx; i; i--) {
		for (int j = 0; j < n; j++) cout << ".#"[cnt[j] >= i];
		cout << '\n';
	}
	cout << string(n, '-') << '\n';
}