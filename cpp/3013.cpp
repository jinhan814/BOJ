#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

int n, k, pos;
int P[100'001];
int C[200'001][2];
i64 res;

int main() {
	fastio;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		int t; cin >> t; t -= k;
		P[i] = P[i - 1] + (t ? t > 0 ? 1 : -1 : 0);
		if (!t) pos = i;
	}
	for (int i = pos; i--;) C[P[i] + 100'000][i & 1]++;
	for (int i = pos; i <= n; i++) res += C[P[i] + 100'000][~i & 1];
	cout << res << '\n';
}