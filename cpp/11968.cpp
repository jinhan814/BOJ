#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, cnt = 0; cin >> n;
	bitset<100'001> check;
	for (int i = 0; i < n; i++) {
		int t; cin >> t;
		check[t] = 1;
	}

	n <<= 1;
	for (int i = 1, j = 1; ;) {
		while (i <= n && !check[i]) i++;
		while (j < i || j <= n && check[j]) j++;
		if (i > n || j > n) break;
		cnt++, i++, j++;
	}
	cout << cnt << '\n';
}