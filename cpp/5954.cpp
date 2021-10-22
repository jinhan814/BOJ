#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int bias = 500'000, MOD = 1e6;
bitset<bias << 1 | 1> B;
int DP[2][bias << 1 | 1];

int main() {
	fastio;
	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];

	int mn = 0; B[bias + 0] = 1;
	for (int i = 0; i < n; i++) B = B << v[i] | B >> v[i];
	for (; ; mn++) if (B[bias + mn] || B[bias - mn]) break;

	DP[0][bias] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= bias << 1; j++) {
			if (j - v[i] >= 0) DP[1][j - v[i]] += DP[0][j];
			if (j + v[i] <= bias << 1) DP[1][j + v[i]] += DP[0][j];
		}
		for (int j = 0; j <= bias << 1; j++) {
			DP[0][j] = DP[1][j] % MOD;
			DP[1][j] = 0;
		}
	}
	cout << mn << ' ' << DP[0][bias + mn] << '\n';
}