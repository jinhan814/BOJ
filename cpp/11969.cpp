#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, q, pSum[3][100'001];

int main() {
	fastio;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		int t; cin >> t; pSum[t - 1][i]++;
		for (int j = 0; j < 3; j++) pSum[j][i] += pSum[j][i - 1];
	}
	while (q--) {
		int a, b; cin >> a >> b;
		for (int j = 0; j < 3; j++) cout << pSum[j][b] - pSum[j][a - 1] << ' ';
		cout << '\n';
	}
}