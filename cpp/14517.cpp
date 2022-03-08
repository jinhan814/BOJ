#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 10007;

int n, res; string s;
int DP[1001][1000];
int P[1001][1000];

int main() {
	fastio;
	cin >> s; n = s.size();
	for (int i = 1; i <= n; i++) {
		// 1. DP 갱신
		for (int j = 0; j <= n - i; j++) {
			if (s[j] != s[j + i - 1]) continue;
			DP[i][j] = 1 + (i > 2 ? P[i - 2][j + 1] : 0);
			if (DP[i][j] >= MOD) DP[i][j] -= MOD;
			res += DP[i][j];
			if (res >= MOD) res -= MOD;
		}
		// 2. pSum 갱신
		for (int j = 0; j < n; j++) {
			P[i][j] = DP[i][j];
			if (i > 0) P[i][j] += P[i - 1][j] + P[i - 1][j + 1];
			if (i > 1) P[i][j] -= P[i - 2][j + 1];
			while (P[i][j] >= MOD) P[i][j] -= MOD;
			if (P[i][j] < 0) P[i][j] += MOD;
		}
	}
	cout << res << '\n';
}