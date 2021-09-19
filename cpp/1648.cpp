#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 9901;
int16_t n, m, cache[14 * 14][1 << 14];

int16_t DFS(int cur, int state) {
	if (cur == n * m) return !state;
	int16_t& ret = cache[cur][state];
	if (ret != -1) return ret;
	if (state & 1) return ret = DFS(cur + 1, state >> 1);
	ret = DFS(cur + 1, state >> 1 | 1 << m - 1);
	if ((cur + 1) % m && ~state & 2) ret += DFS(cur + 2, state >> 2);
	return ret %= MOD;
}

int main() {
	fastio;
	memset(cache, -1, sizeof cache);
	cin >> n >> m;
	cout << DFS(0, 0) << '\n';
}