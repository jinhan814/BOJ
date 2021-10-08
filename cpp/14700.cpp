#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 1e9 + 7;
int n, m, mask, DP[301][1 << 18];

int Sol(int pos, int state) {
	if (pos == n * m) return 1;
	int& ret = DP[pos][state];
	if (ret != -1) return ret; ret = Sol(pos + 1, state << 1 & mask);
	int x = pos / n, y = pos % n, cnt = 0;
	if (state & 1 << n - 1) cnt++;
	if (y && state & 1) cnt++;
	if (y && state & 1 << n) cnt++;
	if (cnt != 3) ret += Sol(pos + 1, state << 1 & mask | 1);
	return ret %= MOD;
}

int main() {
	fastio;
	memset(DP, -1, sizeof DP);
	cin >> n >> m;
	if (n > m) swap(n, m);
	mask = (1 << n + 1) - 1;
	cout << Sol(0, 0) << '\n';
}   