#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int cache[100][100];

int Binomial(int n, int r) {
	if (r == 0 || r == n) return 1;
	int& ret = cache[n][r];
	if (ret) return ret;
	return ret = Binomial(n - 1, r - 1) + Binomial(n - 1, r);
}

int32_t main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		cout << Binomial(9 + n, n) << '\n';
	}
}