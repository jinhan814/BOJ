#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

bool IsAscending(int n) {
	for (int prv = -1; n; n /= 10) {
		if (prv != -1 && n % 10 + 1 != prv) return 0;
		prv = n % 10;
	}
	return 1;
}

int main() {
	fastio;
	int n, mx = -1; cin >> n;
	vector<int> v(n);
	for (auto& i : v) cin >> i;
	for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++)
		if (IsAscending(v[i] * v[j])) mx = max(mx, v[i] * v[j]);
	cout << mx << '\n';
}