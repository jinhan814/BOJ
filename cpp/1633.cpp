#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int _DP[2][16][16];
auto DP = _DP[0], nxt = _DP[1];

int main() {
	fastio;
	int ans = 0; memset(_DP, -1, sizeof _DP); DP[0][0] = 0;
	for (int a, b; cin >> a >> b; swap(DP, nxt)) {
		memcpy(nxt, DP, 1024);
		for (int t1 = 0; t1 <= 15; t1++) for (int t2 = 0; t2 <= 15; t2++) {
			if (DP[t1][t2] == -1) continue;
			if (t1 < 15) nxt[t1 + 1][t2] = max(nxt[t1 + 1][t2], DP[t1][t2] + a);
			if (t2 < 15) nxt[t1][t2 + 1] = max(nxt[t1][t2 + 1], DP[t1][t2] + b);
		}
		ans = max(ans, nxt[15][15]);
	}
	cout << ans << '\n';
}