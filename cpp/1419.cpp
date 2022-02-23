#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int Sol(int l, int r, int k) {
	if (k & 1) {
		const int t = k + 1 >> 1;
		const int L = (l + k - 1) / k;
		const int R = r / k;
		if (t > R) return 0;
		return R - max(L, t) + 1;
	}
	else {
		const int t = k + 1;
		const int L = (l + k / 2 - 1) / (k / 2);
		const int R = r / (k / 2);
		const int bias = (k == 4) * (L <= 6 && 6 <= R);
		if (t > R) return 0;
		return R - max(L, t) + 1 - bias;
	}
}

int main() {
	fastio;
	int l, r, k; cin >> l >> r >> k;
	cout << Sol(l, r, k) << '\n';
}