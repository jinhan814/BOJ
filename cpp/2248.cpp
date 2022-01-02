#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int DP[32][32];

int Binomial(int n, int r) { // n자리 이진수 중 1인 비트가 r개인 이진수의 개수 = nCr
	if (r < 0 || r > n) return 0;
	if (r == 0 || r == n) return 1;
	int& ret = DP[n][r];
	if (ret != -1) return ret;
	return ret = Binomial(n - 1, r - 1) + Binomial(n - 1, r);
}

string Trace(int n, int m, int k) { // n자리, 1인 비트가 m개 이하인 k번째 이진수
	if (!n || !m) return string(n, '0');
	int t = 0;
	for (int i = 0; i <= m; i++) t += Binomial(n - 1, i);
	if (k <= t) return "0" + Trace(n - 1, m, k);
	return "1" + Trace(n - 1, m - 1, k - t);
}

int32_t main() {
	fastio;
	memset(DP, -1, sizeof DP);
	int n, m, k; cin >> n >> m >> k;
	cout << Trace(n, m, k) << '\n';
}