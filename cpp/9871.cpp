#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, q;
int DP[20][100'001];
int v[100'001], _v[100'001];

void SparseInit() {
	for (int j = 1; j < 20; j++) for (int i = 1; i <= n; i++)
		DP[j][i] = DP[j - 1][DP[j - 1][i]];
}

void Init() {
	iota(v + 1, v + n + 1, 1);
	for (int j = 0, t = n - m + 1; t; j++, t >>= 1) {
		if (t & 1) {
			for (int i = 1; i <= n; i++) _v[DP[j][i]] = v[i];
			for (int i = 1; i <= n; i++) v[i] = _v[i];
		}
	}
	rotate(v + 1, v + m, v + n + 1);
	reverse(v + 1, v + n + 1);
}

int main() {
	fastio;
	cin >> n >> m >> q;
	for (int i = 1; i <= m; i++) cin >> DP[0][i];
	for (int i = m + 1; i <= n; i++) DP[0][i] = i;

	for (int i = 1; i <= n; i++)
		if (DP[0][i] == 1) DP[0][i] = n;
		else DP[0][i]--;

	for (SparseInit(), Init(); q--;) {
		int t; cin >> t;
		cout << v[t] << '\n';
	}
}