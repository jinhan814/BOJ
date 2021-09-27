#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, ans, cache[2][3001][3];
auto DP = cache[0], nxt = cache[1];

int main() {
	fastio;
	cin >> n >> m;
	memset(cache, -1, sizeof cache); DP[0][0] = 0;
	while (n--) {
		int val; cin >> val;
		for (int i = 0; i <= m; i++) {
			nxt[i][0] = max({ DP[i][0], DP[i][1], DP[i][2] });
			nxt[i][1] = i ? DP[i - 1][0] : -1;
			nxt[i][2] = -1;
			if (i > 1 && DP[i - 1][1] != -1) nxt[i][2] = max(nxt[i][2], DP[i - 1][1] + val);
			if (i > 1 && DP[i - 1][2] != -1) nxt[i][2] = max(nxt[i][2], DP[i - 1][2] + val);
		}
		swap(DP, nxt);
		ans = max({ ans, DP[m][0], DP[m][1], DP[m][2] });
	}
	cout << ans << '\n';
}