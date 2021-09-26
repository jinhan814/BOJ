#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, k, mx = 0; cin >> n >> k;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i], v[i] &= 1;

	for (int l = 0, r = 0, sum = 0; l < n;) {
        while (r < n && sum + v[r] <= k) sum += v[r++];
		mx = max(mx, r - l - sum); sum -= v[l++];
	}
	cout << mx << '\n';
}